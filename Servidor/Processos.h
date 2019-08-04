/* 
 * File:   Processos.h
 * Author: dev
 *
 * Created on 3 de Agosto de 2019, 02:22
 */

#ifndef PROCESSOS_H
#define PROCESSOS_H

#include "Conta.h"
#include "Lib/Msg.h"
#include "BancoDB.h"

// Tipo de mensagem para autenticação.
#define TYPE_AUTH       'A' // Para pacote Recebido
#define TYPE_AUTH_SUCE  'A' // Para pacote de Sucesso
#define TYPE_AUTH_FAIL  'a' // Para pacote de Falha

// Tipo de mensagem para criar conta
#define TYPE_CREA       'C' // Para pacote Recebido
#define TYPE_CREA_SUCE  'C' // Para pacote de Sucesso
#define TYPE_CREA_FAIL  'c' // Para pacote de Falha

using namespace std;

class Processos {
    
public:
    Processos();
    Processos(const Processos& orig);
    virtual ~Processos();
    
    void setHandle(int handle);
    int getHandle();
    
    void setBancoDB(BancoDB *db);
    BancoDB *getBancoDB();
    
    void setConta(Conta *acc);
    Conta *getConta();
    
    int start();
    static void run(Processos *proc);
    
private:
    int handle;
    Conta *conta;
    BancoDB *dbc;
    
    // Metodo responsavel por autenticar (ou não) a conta do cliente.
    static Conta *autenticar(Processos *proc, Msg *msg);
    
    // Metodo responsavel por cadastrar novo usuario
    static Conta *cadastrarUser(Processos *proc, Msg *msg);
    
    // Envia para o cliente a resposta da operação, se funcionou ou não.
    static int enviaResultado(Processos *proc, char tipo);
    
};

#endif /* PROCESSOS_H */

