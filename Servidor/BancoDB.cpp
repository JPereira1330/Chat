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
    for (list<Conta *>::iterator it = this->contas.begin(); it != this->contas.end(); ++it) {
        delete(*it);
    }
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

int BancoDB::encontrarHandle(int login){

    for (list<Conta *>::iterator it = this->contas.begin(); it != this->contas.end(); ++it){
        if( (*it)->GetLogin() == login ){
            return (*it)->getHandle();
        }
    }
    
    return 0;
}

int BancoDB::salvarDB(){
    
    DBCONTA dbconta;
    FILE *fp;
    fp = fopen(DIR_BANCO, "w");

    if (!fp) {
        return 0;
    }

    for (list<Conta *>::iterator it = this->contas.begin(); it != this->contas.end(); ++it) {
        dbconta.login = (*it)->GetLogin();
        dbconta.senha = (*it)->GetSenha();
        snprintf(dbconta.nome, sizeof(dbconta.nome), "%s", (*it)->GetNome().c_str());
        fwrite(&dbconta,1,sizeof(DBCONTA), fp);
    }

    fclose(fp);
    return 1;
}

int BancoDB::carregarDB(){
    
    DBCONTA dbconta;
    FILE *fp;
    fp = fopen(DIR_BANCO, "r");
    int lenFile, totalContas;
    Conta *conta;
    
    if(contas.size()){
        return 0;
    }
    
    if(!fp){
        return 0;
    }
    
    fseek(fp, 0L, SEEK_END);
    lenFile = ftell(fp);
    rewind(fp);
    totalContas = lenFile / sizeof(DBCONTA);
    
    for(int i = 0; i < totalContas; i++){
        fread(&dbconta,1,sizeof(DBCONTA), fp);
        
        conta = new Conta();
        conta->SetLogin(dbconta.login);
        conta->SetSenha(dbconta.senha);
        conta->SetNome(string(dbconta.nome));
        
        this->add(conta);
    }
    
    return 1;
}