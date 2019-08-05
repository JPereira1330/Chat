/* 
 * File:   Processos.cpp
 * Author: dev
 * 
 * Created on 1 de agosto de 2019, 12:07
 */

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Processos.h"
#include "Interface.h"
#include "Lib/sys_log.h"
#include "Lib/SocketClient.h"
#include "Lib/Msg.h"

Processos::Processos() {
}

Processos::Processos(const Processos& orig) {
}

Processos::~Processos() {
}

SocketClient *Processos::getSocketClient(){
    return this->sc;
}

int Processos::setSocketClient(SocketClient* sc){
    this->sc = sc;
}

int Processos::start(){
    
    int ret;
    Conta *conta;

    Interface inter;
    
    conta = new Conta();
        
    log_write("Capturando credenciais de acesso.");
    inter.printTelaLogin(conta);
    
    log_write("Incializando conexão.");
    ret = this->getSocketClient()->connectSocket();
    
    if( ret == 0 ){
        log_write("Não foi possivel se conectar ao servidor.");
        return 0;
    }
      
    ret = autenticar(conta);
    
    switch(ret){
        case 1:
            inter.printTelaPrincipal(conta);
            
            break;
        case 0:
            log_write("Nao foi encontrado o usuario informado, criando um novo.");
            inter.printCriarConta(conta);
            criarConta(conta);
            start();
            break;
    }
    
    return 1;
}

int Processos::autenticar(Conta *conta){
    
    Msg *msg;
    char *buffer;
    unsigned int ret;
    unsigned int len;
    
    log_write("Autenticador - Criando pacote de comunicação.");
    msg = new Msg();
    msg->setType(TYPE_AUTH);
    msg->add(conta->GetLogin());
    msg->add(conta->GetSenha());
    
    len = msg->getBuffer(&buffer);
    log_write("Autenticador - Tamanho do buffer da mensagem: %d bytes", len);
    
    if(len == 0){
        log_write("Autenticador - Ocorreu um erro ao montar o pacote.");
        delete(msg);
        return 0;
    }
    
    len = this->getSocketClient()->writeSocket(buffer,len);
    log_write("Autenticador - Bytes enviados para o servidor: %d bytes", len);

    if(len == 0){
        log_write("Autenticador - Ocorreu um erro durante o envio dos dados.");
        delete(msg);
        return 0;
    }
   
    ret = getServerReturn(msg);
   
    if(ret == 0){
        log_write("Ocorreu um erro ao receber os dados do servidor");
        return 0;
    }
    
    if(msg->getType() == TYPE_AUTH){
        conta->SetSenha(0);
        conta->SetAuth(true);
    }else{
        conta->SetSenha(0);
        conta->SetAuth(false);
    }
    
    // Limpando memoria
    free(buffer);
    free(msg);
    
    log_write("[TEMP] Autenticacao: %d", conta->IsAuth());
    
    return 1;
}

int Processos::criarConta(Conta *conta){
   
    Msg *msg;
    char *buffer;
    unsigned int len;
    
    log_write("Criando pacote para comunicação.");
    msg = new Msg();
    msg->setType('C');
    msg->add(conta->GetLogin());
    msg->add(conta->GetSenha());
    
    len = msg->getBuffer(&buffer);
    log_write("Buffer de %d bytes.", len);
    
    if(len == 0){
        log_write("Tamanho do buffer invalido.");
        free(buffer);
        delete(msg);
        return 0;
    }
    
    log_write("Enviando %d Bytes para o servidor.", len);
    len = this->getSocketClient()->writeSocket(buffer, len);
    log_write("Enviado %d Bytes.", len);
    
    if(len == 0){
        log_write("Ocorreu um erro durante o envio.");
        free(buffer);
        delete(msg);
        return 0;
    }
    
    log_write("Aguardando resposta do servidor.");
    len = getServerReturn(msg);
    
    if(len == 0){
        log_write("Ocorreu um erro na leitura da resposta do servidor.");
        free(buffer);
        delete(msg);
        return 0;
    }
    
    switch(msg->getType()){
        case 'C':
            log_write("Conta criada com sucesso!");
            return 1;
            break;
        case 'c':
            log_write("Conta nao foi criada.");
            free(buffer);
            delete(msg);
            return 0;
            break;
        default:
            log_write("Ocorreu algum erro nao indentificado.");
            free(buffer);
            delete(msg);
            return 0;
            break;
    }
    
    return 0;
}

int Processos::getServerReturn(Msg* msg){
    
    char tipo;
    char *buffer;
    unsigned int len;
    unsigned int ret;
    
    // Capturando tamanho do buffer
    ret = getSocketClient()->readSocket(&len, sizeof(unsigned int));
    
    if(ret < 0){
        log_write("Erro de leitura");
        return 0;
    }
    
    // Capturando tipo do pacote
    ret = getSocketClient()->readSocket(&tipo, sizeof(char));
    
    if(ret < 0){
        log_write("Erro de leitura");
        return 0;
    }
    
    msg->setType(tipo);
        
    if(len == 0){       // Caso só receba o tipo
        return 1;
    }
    
    // Continua caso tenha mais dados no pacote.
    buffer = (char *) malloc(len);
    ret = getSocketClient()->readSocket(&buffer, len);
    
    if(ret <= 0){
        free(buffer);
        return 0;
    }
    
    msg->setBuffer(buffer, len);
    free(buffer);
    
    return 1;
}