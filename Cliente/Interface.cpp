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

int Interface::printTelaInicial(){
    
    int op;
    
    cout << " [ C H A T ] " << endl;
    cout << " [ 1 ] Ja possuo uma conta." << endl;
    cout << " [ 2 ] Cadastrar uma nova conta. " << endl;
    cout << " [ 9 ] Sair do programa." << endl;
    cout << " [ * ] Opção: ";
    fflush(stdout);
    
    cin >> op;
    
    return op;
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
        login = conta->GetLogin();
    }
    
    // Capturando a senha do usuario caso ainda não tenha
    if(conta->GetSenha() == 0){
        cout << "Senha: ";
        fflush(stdout);
        cin >> senha;
        cout << endl;
    }else{
        cout << "Senha: " << conta->GetSenha() << endl;
        senha = conta->GetSenha();
    }
    
    // Capturando o nome do usuario caso ainda não tenha
    if(conta->GetNome().empty()){
        cout << "Nome: ";
        fflush(stdout);
        cin >> nome;
        cout << endl;
    }else{
        cout << "Nome: " << conta->GetNome() << endl;
        nome = conta->GetNome();
    }
    
    conta->SetLogin(login);
    conta->SetSenha(senha);
    conta->SetNome(nome);
    
    return;
}

int Interface::printTelaPrincipal(Conta* conta){
 
    int numero;
    
    cout << " [ CHAT - " << conta->GetNome() << " ]" << endl;
    cout << " [ * ] Conversar com: ";
    fflush(stdout);
    cin >> numero;
    
    return numero;
}