/* 
 * File:   Interface.cpp
 * Author: dev
 * 
 * Created on 1 de agosto de 2019, 11:58
 */

#include <iostream>
#include <string>
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

void Interface::printCriarConta(Conta* conta){
    
    int login;
    int senha;
    string nome;

    cout << " [ CRIANDO CONTA ] " << endl;
    
    // Caputando o login do cliente caso ainda não tenha
    if(conta->GetLogin() == 0){
        cout << "Login: ";
        fflush(stdout);
        cin >> login;
        cout << endl;
    }else{
        cout << "Login: " << conta->GetLogin() << endl;
    }
    
    // Capturando a senha do usuario caso ainda não tenha
    if(conta->GetSenha() == 0){
        cout << "Senha: ";
        fflush(stdout);
        cin >> senha;
        cout << endl;
    }
    
    // Capturando o nome do usuario caso ainda não tenha
    if(conta->GetNome().empty()){
        cout << "Nome: ";
        fflush(stdout);
        cin >> nome;
        cout << endl;
    }
    
    conta->SetLogin(login);
    conta->SetSenha(senha);
    conta->SetNome(nome);
    
    return;
}

void Interface::printTelaPrincipal(Conta* conta){
    
}