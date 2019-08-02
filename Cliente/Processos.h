/* 
 * File:   Processos.h
 * Author: dev
 *
 * Created on 1 de agosto de 2019, 12:07
 */

#ifndef PROCESSOS_H
#define PROCESSOS_H

#include "Conta.h"
#include "Lib/SocketClient.h"

class Processos {
    
public:
    Processos();
    Processos(const Processos& orig);
    virtual ~Processos();
    
    SocketClient *getSocketClient();
    int setSocketClient(SocketClient* sc);
    
    int start();
    
private:
    SocketClient *sc;
    
    int run(Conta *conta);
    
};

#endif /* PROCESSOS_H */

