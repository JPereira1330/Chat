/* 
 * File:   Conta.h
 * Author: dev
 *
 * Created on 2 de Agosto de 2019, 02:38
 */

#ifndef CONTA_H
#define CONTA_H

class Conta {
public:
    Conta();
    Conta(int login, int senha);
    Conta(const Conta& orig);
    virtual ~Conta();
    
    bool IsAuth();
    void SetAuth(bool auth);
    
    int GetLogin();
    void SetLogin(int login);
    
    int GetSenha();
    void SetSenha(int senha);
    
    char* GetNome();
    void SetNome(char* nome);
    
private:
    int login;
    int senha;
    bool auth;
    char *nome;
    
};

#endif /* CONTA_H */

