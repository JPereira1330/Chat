/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Processos.cpp
 * Author: dev
 * 
 * Created on 3 de Agosto de 2019, 02:22
 */

#include <thread>
#include <stdlib.h>
#include "Processos.h"
#include "Lib/sys_log.h"

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

int Processos::start(){
 
    log_write("Carregando Banco de dados");
    BancoDB->carregarArquivo();
    
    thread runThread(Processos::run, this);
    runThread.detach();
    
    return 1;
}

void Processos::run(Processos *pro){
    
    int len;
    
    do{
        len = 0;
        log_write("[Handle %d] - Aguardando pacote.", pro->getHandle());
        
        
    }while(1);
    
}