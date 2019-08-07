/* 
 * File:   BancoDB.h
 * Author: dev
 *
 * Created on 5 de Agosto de 2019, 00:26
 */

#ifndef BANCODB_H
#define BANCODB_H

#include <list>
#include <string.h>
#include "Conta.h"

#define DIR_BANCO "banco.db"

using namespace std;

typedef struct dbconta{
    int login;
    int senha;
    char nome[32];
} DBCONTA;

class BancoDB {
public:
    BancoDB();
    BancoDB(const BancoDB& orig);
    virtual ~BancoDB();

    /**
     * Adiciona conta na lista.
     * @param conta - > Objeto conta a ser adicionado
     */
    void add(Conta *conta);
    
    /**
     * Procura e retorna a conta do usuario pela numero da conta.
     * @param login -> Numero da login
     * @return Ponteiro de conta
     */
    Conta *encontrar(int login);
    
    /**
     * Procura e retorna o handle do usuario pela numero da conta.
     * @param login -> Numero da login
     * @return Ponteiro de conta
     */
    int encontrarHandle(int login);
    
    /**
     * Salva o banco de dados num arquivo
     * @return 0 fail, 1 true. 
     */
    int salvarDB();
    
    /**
     * Carrega o banco de dados para a memoria.
     * @return 0 fail, 1 true.
     */
    int carregarDB();
    
private:
    list<Conta *> contas;
    
};

#endif /* BANCODB_H */

