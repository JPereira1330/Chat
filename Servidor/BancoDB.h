
/* 
 * File:   BancoDB.h
 * Author: dev
 *
 * Created on 3 de Agosto de 2019, 02:21
 */

#ifndef BANCODB_H
#define BANCODB_H

#include <list>
#include <string.h>
#include "Conta.h"

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
     * Adiciona conta na lista
     * @param conta
     * @return 0 fail, 1 true.
     */
    void adicionarConta(Conta *conta);
    
    /**
     * Salva a lista num arquivo
     * @return 0 fail, 1 true.
     */
    int salvarArquivo();
    
    /**
     * Carrega os daados da lista
     * @return 0 fail, 1 true.
     */
    int carregarArquivo();
    
    /**
     * Procura uma determinada conta na lista
     * @param idConta Numero da conta que deverá ser encontrada
     * @return Conta encontrada
     */
    Conta *procurarConta(int login);
    
private:
    list<Conta *> contas;
    
};

#endif /* BANCODB_H */

