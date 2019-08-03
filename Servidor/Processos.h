/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Processos.h
 * Author: dev
 *
 * Created on 3 de Agosto de 2019, 02:22
 */

#ifndef PROCESSOS_H
#define PROCESSOS_H

#include <thread>
#include "Lib/Msg.h"
#include "BancoDB.h"

using namespace std;

class Processos {
    
public:
    Processos();
    Processos(const Processos& orig);
    virtual ~Processos();
    
    void setHandle(int handle);
    int getHandle();
    
    int start();
    static void run(Processos *proc);
    
private:
    int handle;
    
    
};

#endif /* PROCESSOS_H */

