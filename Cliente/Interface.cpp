/* 
 * File:   Interface.cpp
 * Author: dev
 * 
 * Created on 1 de agosto de 2019, 11:58
 */

#include <iostream>
#include "Interface.h"
#include "Conta.h"

Interface::Interface() {
}

Interface::Interface(const Interface& orig) {
}

Interface::~Interface() {
}

void Interface::printTelaLogin(Conta *conta){
    
    int log;
    int sen;
    
    cout << " [ * ] Login " << endl;
    scanf("%d", &log);
    
    cout << " [ * ] Senha " << endl;
    scanf("%d", &sen);

    conta->SetLogin(log);
    conta->SetSenha(sen);
    
    return;
}