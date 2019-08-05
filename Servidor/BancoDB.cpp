/* 
 * File:   BancoDB.cpp
 * Author: dev
 * 
 * Created on 5 de Agosto de 2019, 00:26
 */

#include <list>
#include "BancoDB.h"

BancoDB::BancoDB() {
}

BancoDB::BancoDB(const BancoDB& orig) {
}

BancoDB::~BancoDB() {
}

void BancoDB::add(Conta *conta){
    this->contas.push_back(conta);
}

Conta *BancoDB::encontrar(int login){
    
    for (list<Conta *>::iterator it = this->contas.begin(); it != this->contas.end(); ++it){
        if( (*it)->GetLogin() == login ){
            return *it;
        }
    }
    
    return NULL;
}

int BancoDB::salvarDB(){
    return 1;
}

int BancoDB::carregarDB(){
    
    Conta *acc;
    
    acc = new Conta();
    acc->SetLogin(666);
    acc->SetSenha(555);
      
    this->add(acc);
    
    return 1;
}