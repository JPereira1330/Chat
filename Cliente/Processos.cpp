/* 
 * File:   Processos.cpp
 * Author: dev
 * 
 * Created on 1 de agosto de 2019, 12:07
 */

#include <iostream>
#include <string>
#include <cstring>
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
    
    log_write("Start - Capturando credenciais de acesso.");
    inter.printTelaLogin(conta);
    
    log_write("Start - Incializando conexão.");
    ret = this->getSocketClient()->connectSocket();
    
    if( ret == 0 ){
        log_write("Start - Não foi possivel se conectar.");
        return 0;
    }
      
    autenticar(conta);
    
    cout << conta->IsAuth();
    
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
   
    ret = capturarTipo();
    delete(msg);
   
    if(ret == TYPE_AUTH){
        conta->SetSenha(0);
        conta->SetAuth(true);
    }else{
        conta->SetSenha(0);
        conta->SetAuth(false);
    }
    
    cout << conta->IsAuth();
    return 1;
}

char Processos::capturarTipo(){
    
    char tipo;
    unsigned int len;
    unsigned int lenBuffer;
    
    len = this->getSocketClient()->readSocket(&lenBuffer, sizeof(unsigned int));
    log_write("Autenticador - Bytes Recebidos do servidor: %d bytes, Buffer: %d bytes.", len, lenBuffer);
    
    if(len == 0){
        log_write("Autenticador - Ocorreu um erro durante o recebimento dos dados.");
        return 0;
    }
    
    len = this->getSocketClient()->readSocket(&tipo, lenBuffer);
    log_write("Autenticador - Bytes Recebidos do servidor: %d bytes", len);
    
    if(len == 0){
        log_write("Autenticador - Ocorreu um erro durante o recebimento do tipo.");
        return 0;
    }
    
    return tipo;
}