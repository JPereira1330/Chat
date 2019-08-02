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
    Conta(const Conta& orig);
    virtual ~Conta();
    
    bool IsAuth();
    void SetAuth(bool auth);
    
    int GetLogin();
    void SetLogin(int login);
    
    int GetSenha();
    void SetSenha(int senha);
    
private:
    int login;
    int senha;
    bool auth;
    
};

#endif /* CONTA_H */

