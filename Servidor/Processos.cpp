/* 
 * File:   Processos.cpp
 * Author: dev
 * 
 * Created on 3 de Agosto de 2019, 02:22
 */

#include <stdlib.h>
#include "Processos.h"
#include "Lib/sys_log.h"
#include "Lib/SocketServer.h"

Processos::Processos() {
}

Processos::Processos(const Processos& orig) {
}

Processos::~Processos() {
}

void Processos::setHandle(int handle){
    this->handle = handle;
}

int Processos::getHandle(){
    return this->handle;
}

void Processos::setBancoDB(BancoDB *db){
    this->dbc = db;
}

BancoDB *Processos::getBancoDB(){
    return this->dbc;
}

void Processos::setConta(Conta *acc){
    this->conta = conta;
}

Conta *Processos::getConta(){
    return this->conta;
}

int Processos::start(){
 
    log_write("Carregando Banco de dados");
    //BancoDB->carregarArquivo();
    
    run(this);
    
    return 1;
}

void Processos::run(Processos *proc){
    
    int ret;
    Msg *msg;
    char tipo;
    char *buffer;
    unsigned int lenBuffer;
    
    do{
        
        // Caputrando o tamanho do pacote
        log_write("[Handle %d] - Aguardando tamanho pacote.", proc->getHandle());
        ret = SocketServer::readSocket(proc->getHandle(), &lenBuffer, sizeof(unsigned int));
        if( ret == 0 ){
            log_write("[Handle %d] - Erro ao receber tamanho do pacote.", proc->getHandle());
            // Desligacar conexão com cliente.
            return;
        }
        
        // Captraundo o tipo do pacote
        log_write("[Handle %d] - Aguardando tipo do pacote.", proc->getHandle());
        ret = SocketServer::readSocket(proc->getHandle(), &tipo, sizeof(char));
        log_write("[Handle %d] - Tipo recebido %c com %d bytes", proc->getHandle(), tipo, ret);
        if( ret == 0 ){
            log_write("[Handle %d] - Erro ao receber tipo.", proc->getHandle());
            // Desligar conexão com o cliente.
            return;
        }
        
        msg = new Msg();
        
        // Capturando o conteudo do pacote caso ajá.
        log_write("[Handle %d] - Aguardando buffer de %d bytes do usuario e senha.", proc->getHandle(), lenBuffer);
        if(lenBuffer > 0){
            
            buffer = (char *) malloc(lenBuffer);
            ret = SocketServer::readSocket(proc->getHandle(), buffer, lenBuffer);
            
            if( ret == 0 ){
                log_write("[Handle %d] - Erro ao receber buffer.", proc->getHandle());
                // Desliga conexão com o cliente.
                delete(msg);
                return;
            }
            
            msg->setBuffer(buffer, lenBuffer);
        }
        
        switch(tipo){
            case TYPE_AUTH:
                log_write("[Handle %d] - Solicita autenticacao.", proc->getHandle());
                proc->setConta(autenticar(proc, msg));
                break;
            case TYPE_CREA:
                log_write("[Handle %d] - Solicita criar conta.", proc->getHandle());
                proc->cadastrarUser(proc, msg);
                break;
            default:
                // Tipo n definido
                break;
        }
        
    }while(1);
    
}

Conta *Processos::cadastrarUser(Processos *proc, Msg *msg){
 
    int login;
    int senha;
    Conta *conta;
    
    msg->next(&login);
    log_write("[Handle %d] - Usuario recebido: %d.", proc->getHandle(), login);
    
    msg->next(&senha);
    log_write("[Handle %d] - Senha recebida: %d.", proc->getHandle(), senha);   // [TEMP] Retirar depois a senha
    
    if(login == proc->getBancoDB()->procurarConta(login)->GetLogin()){
            log_write("[Handle %d] - Conta já existe.", proc->getHandle());
            enviaResultado(proc, TYPE_CREA_FAIL);
            return NULL;
    }
    
    conta = new Conta(login, senha);
    log_write("[Handle %d] - Conta criada.", proc->getHandle());

    proc->getBancoDB()->adicionarConta(conta);
    log_write("[Handle %d] - Conta adicionada no banco.", proc->getHandle());
    
    return conta;
}

Conta *Processos::autenticar(Processos *proc, Msg *msg){
    
    int login;
    int senha;
    Conta *conta;
    
    msg->next(&login);
    log_write("[Handle %d] - Usuario recebido: %d.", proc->getHandle(), login);
    
    msg->next(&senha);
    log_write("[Handle %d] - Senha recebida: %d.", proc->getHandle(), senha);   // [TEMP] Retirar depois a senha
    
    conta = new Conta();
    log_write("[Handle %d] - Procurando por conta.", proc->getHandle());
    conta = proc->getBancoDB()->procurarConta(login);
    
    if(conta != NULL){
        log_write("[Handle %d] - Conta nao encontrada.", proc->getHandle());
        enviaResultado(proc, TYPE_AUTH_FAIL);
        delete(conta);
        return NULL;
    }
    
    if(conta->GetSenha() == senha){
        conta->SetAuth(true);
        enviaResultado(proc, TYPE_AUTH_SUCE);
        log_write("[Handle %d] - Conta autenticada.", proc->getHandle());
    }else{
        conta->SetAuth(false);
        log_write("[Handle %d] - Conta nao autenticada.", proc->getHandle());
        enviaResultado(proc, TYPE_AUTH_FAIL);
        delete(conta);
        return NULL;
    }
    
    return conta;
}

int Processos::enviaResultado(Processos *proc, char tipo){
    
    int len;
    Msg *msg;
    char *buffer;
        
    msg = new Msg();
    msg->setType(tipo);
    
    len = msg->getBuffer(&buffer);
    log_write("[Handle %d] - Buffer de %d gerado", proc->getHandle(), len);
    
    if(len == 0){
        log_write("[Handle %d] - Ocorreu um erro ao gerar o buffer de envio.", proc->getHandle());
        delete(msg);
        return 0;
    }
    
    len = SocketServer::writeSocket(proc->getHandle(), buffer, len);
    log_write("[Handle %d] -Total de %d bytes enviados.", proc->getHandle(), len);
    
    if(len == 0){
        log_write("[Handle %d] - Ocorreu um erro ao enviar resposta.", proc->getHandle());
        delete(msg);
        return 0;
    }
    
    return 1;
}