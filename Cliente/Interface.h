/* 
 * File:   Interface.h
 * Author: dev
 *
 * Created on 1 de agosto de 2019, 11:58
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include "Conta.h"

using namespace std;

class Interface {

public:
    Interface();
    Interface(const Interface& orig);
    virtual ~Interface();
    
    int printTelaInicial();
    void printTelaLogin(Conta* conta);
    void printCriarConta(Conta* conta);
    int printTelaPrincipal(Conta* conta);

private:

};

#endif /* INTERFACE_H */

