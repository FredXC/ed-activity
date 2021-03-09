#include <iostream>
#include "configuracao.hpp"

using namespace std;

class noh {
friend class ArvoreBplus;
private:
    bool folha;
    unsigned numElementos; // número de itens armazenadas no nó
    chave itens[CAP_PACOTE+1];
    noh* filhos[CAP_PACOTE+1];
    int posFilhos[CAP_PACOTE+1];
    noh* pai;
public:
    noh();
    ~noh();
};

noh::noh() {
    numElementos = 0;
    folha = false;
    for (int i = 0; i < CAP_PACOTE+1; i++) {
        filhos[i] = NULL;
    }
}

noh::~noh() {
    for (int i = 0; i < numElementos+1; i++) {
        delete filhos[i];
    }
}

bool primeiraMenor(tipoChave chave1, tipoChave chave2){
    int i;
    for (i = 0; chave1[i] != '\0' && chave2[i] != '\0'; i++){
        //assim que uma letra seja diferente
        if (chave1[i] != chave2[i]){
            //retorna -1 se a primeira for menor ou 1 caso contrário
            return chave1[i] < chave2[i] ? true : false;
        }
    }

    if(chave1[i] - chave2[i] < 0){
        return false;
    }

    return true;
}
