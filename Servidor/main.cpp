/* 
 * File:   main.cpp
 * Author: dev
 *
 * Created on 1 de agosto de 2019, 11:57
 */

#include <cstdlib>
#include "Lib/sys_log.h"
#include "Lib/SocketServer.h"
#include "Processos.h"

#define QUEUE 99

using namespace std;

int main(int argc, char** argv) {

    log_write("Incializando servidor.");
    int hand;
    Processos *proc;
    SocketServer sockSrv;
    BancoDB bdb;
    
    log_write("Configurando socket de comunicação.");
    sockSrv.setPort(atoi(argv[1]));
    sockSrv.setQueue(QUEUE);   
    sockSrv.openSocket();
    
    do{
        
        log_write("Aguardando conexão.");
        hand = sockSrv.acceptSocket();
        log_write("Conexão efetuada com o handler: %d", hand);
        
        proc = new Processos();    
        proc->setHandle(hand);
        proc->setBancoDB(&bdb);
        proc->start();
        
    }while(1);
    
    return 0;
}

