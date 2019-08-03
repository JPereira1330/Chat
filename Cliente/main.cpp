/* 
 * File:   main.cpp
 * Author: dev
 *
 * Created on 1 de agosto de 2019, 11:57
 */

#include <cstdlib>

#include "Processos.h"

using namespace std;

int main(int argc, char** argv) {
    
    Processos proc;
    SocketClient sc;
    
    sc.setIP(argv[1]);
    sc.setPort(atoi(argv[2]));
    
    proc.setSocketClient(&sc);
    proc.start();
    
    return 0;
}

