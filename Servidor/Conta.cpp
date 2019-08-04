/* 
 * File:   Conta.cpp
 * Author: dev
 * 
 * Created on 2 de Agosto de 2019, 02:38
 */

#include "Conta.h"

Conta::Conta() {
    SetAuth(false);
}

Conta::Conta(int login, int senha){
    SetLogin(login);
    SetSenha(senha);
}

Conta::Conta(const Conta& orig) {
}

Conta::~Conta() {
}

bool Conta::IsAuth() {
    return auth;
}

void Conta::SetAuth(bool auth) {
    this->auth = auth;
}

int Conta::GetLogin() {
    return login;
}

void Conta::SetLogin(int login) {
    this->login = login;
}

int Conta::GetSenha(){
    return senha;
}

void Conta::SetSenha(int senha) {
    this->senha = senha;
}

char* Conta::GetNome() {
    return nome;
}

void Conta::SetNome(char* nome) {
    this->nome = nome;
}