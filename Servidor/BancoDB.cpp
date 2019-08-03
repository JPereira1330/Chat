/* 
 * File:   BancoDB.cpp
 * Author: dev
 * 
 * Created on 3 de Agosto de 2019, 02:21
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include "BancoDB.h"
#include "Conta.h"

#define DIR_BANCO "banco.db"

BancoDB::BancoDB() {
}

BancoDB::BancoDB(const BancoDB& orig) {
}

BancoDB::~BancoDB() {
    for (list<Conta *>::iterator it = this->contas.begin(); it != this->contas.end(); ++it) {
        delete(*it);
    }
}

void BancoDB::adicionarConta(Conta* conta) {
    this->contas.push_back(conta);
}

int BancoDB::salvarArquivo() {
    DBCONTA dbconta;
    FILE *fp;
    fp = fopen(DIR_BANCO, "w");

    if (!fp) {
        return 0;
    }

    for (list<Conta *>::iterator it = this->contas.begin(); it != this->contas.end(); ++it) {
        dbconta.login = (*it)->GetLogin();
        dbconta.senha = (*it)->GetSenha();
        snprintf(dbconta.nome, sizeof(dbconta.nome), "%s", (*it)->GetNome());
        fwrite(&dbconta,1,sizeof(DBCONTA), fp);
    }

    fclose(fp);
    return 1;
}

int BancoDB::carregarArquivo() {
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
        conta->SetNome(dbconta.nome);
        this->adicionarConta(conta);
    }
    
    return 1;
}

Conta* BancoDB::procurarConta(int login) {
    
    for (list<Conta *>::iterator it = this->contas.begin(); it != this->contas.end(); ++it) {
        if( (*it)->GetLogin() == login ){
            return *it;
        }
    }
    
    return NULL;
}