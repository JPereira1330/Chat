/* 
 * File:   Conta.cpp
 * Author: dev
 * 
 * Created on 2 de Agosto de 2019, 02:38
 */

#include "Conta.h"

Conta::Conta() {
    SetAuth(0);
    SetLogin(0);
    SetSenha(0);
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

string Conta::GetNome() {
    return nome;
}

void Conta::SetNome(string nome) {
    this->nome = nome;
}

int Conta::getHandle(){
    return this->handle;
}

void Conta::setHandle(int handle){
    this->handle = handle;
}