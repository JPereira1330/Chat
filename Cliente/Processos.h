/* 
 * File:   Processos.h
 * Author: dev
 *
 * Created on 1 de agosto de 2019, 12:07
 */

#ifndef PROCESSOS_H
#define PROCESSOS_H

#include "Conta.h"
#include "Lib/Msg.h"
#include "Lib/SocketClient.h"

#define TYPE_AUTH 'A' // Request para autenticação
#define TYPE_NEWC 'C' // Request para criar conta

class Processos {
    
public:
    Processos();
    Processos(const Processos& orig);
    virtual ~Processos();
    
    SocketClient *getSocketClient();
    int setSocketClient(SocketClient* sc);
    
    int start();
    
private:
    SocketClient *sc;
    
    /**
     * Valida com o servidor se usuario existe.
     * @param conta Objeto conta do usuario que sera manipulado
     * @return 0 fail, 1 true.
     */
    int autenticar(Conta *conta);
    
    /**
     * Envia para o servidor uma conta para ser criada.
     * @param conta Objeto a ser enviado para os servidor
     * @return 0 fail, 1 true.
     */
    int criarConta(Conta *conta);
    
    /**
     * Metodo que captura retorno do servidor quanto a requisição.
     * @return 0 fail, 1 true
     */
    int getServerReturn(Msg *msg);
    
};

#endif /* PROCESSOS_H */

