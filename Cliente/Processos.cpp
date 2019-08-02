/* 
 * File:   Processos.cpp
 * Author: dev
 * 
 * Created on 1 de agosto de 2019, 12:07
 */

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
    
    run(conta);
    
    return 1;
}

int Processos::run(Conta *conta){
    
    Msg* msg;
    char* buffer;
    unsigned int len;

    log_write("Conectar - Criando pacote para comunicação.");
    msg = new Msg();
    msg->setType('C');
    msg->add(conta->GetLogin());
    msg->add(conta->GetSenha());
    
    len = msg->getBuffer(&buffer);  // Dando Falha de semegmentação aki.
    log_write("Conectar - Pacote criado com tamanho de %s bytes", len);
    
    //this->getSocketClient()->writeSocket(buffer, len);
    
    return 1;
}