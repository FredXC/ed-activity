// Árvore 2-3-4
// (Árvore B em memória, com nós com capacidade para 2, 3 ou 4 filhos)
// Estruturas de Dados - 2018/2
// Código by Joukim

#include <iostream>
#include "noh.hpp"

using namespace std;

class ArvoreBplus {
private:
    noh* raiz;
    void percorreEmOrdemAux(noh* atual, int nivel);
public:
    ArvoreBplus() { raiz = NULL; }
    ~ArvoreBplus() { delete raiz; }
    // código não implementado, sua tarefa é implementá-lo!
    void insereFolhaNaoCheio(noh* umNoh, chave umItem);
    noh* divide (noh* umNoh, chave &itemPromovido);
    void insereItermediarioNaoCheio(noh* umNoh, noh* novo, chave &itemPromovido);
    noh* insereAux(noh* umNoh, chave umItem, chave &itemPromovido);
    void insere(chave umItem);
    // percorrimento (impressão)
    void percorreEmOrdem();
    void imprimirPelaArvoreAux(noh *umNoh, int espaco);
    void imprimirPelaArvore();
};

void ArvoreBplus::insereFolhaNaoCheio(noh* umNoh, chave umItem){
    int pos = umNoh->numElementos - 1;
    while ((pos >= 0) and (primeiraMenor(umItem.key, umNoh->itens[pos].key))){
        umNoh->itens[pos+1] = umNoh->itens[pos];
        pos--;
    }
    umNoh->itens[pos+1] = umItem;
    umNoh->numElementos++;
}

noh* ArvoreBplus::divide(noh* umNoh, chave &itemPromovido){
    itemPromovido = umNoh->itens[POS_MEIO];
    noh* novo = new noh();
    novo->folha = umNoh->folha;
    if(umNoh->folha){
        for (int i = 0; i < POS_MEIO+1; i++)
            novo->itens[i] = umNoh->itens[POS_MEIO+i];
        novo->numElementos = POS_MEIO + 1;
        umNoh->numElementos = POS_MEIO;
    }else{
        for (int i = 0; i < POS_MEIO+1; i++)
            novo->itens[i] = umNoh->itens[POS_MEIO+1+i];
        novo->numElementos = POS_MEIO;
        umNoh->numElementos = POS_MEIO;
    }

    if(not(umNoh->folha)){
        for (int i = 0; i < POS_MEIO+1; i++){
            novo->filhos[i] = umNoh->filhos[POS_MEIO+1+i];
        }
    }
    return novo;

}

void ArvoreBplus::insereItermediarioNaoCheio(noh* umNoh, noh* novo, chave &itemPromovido){
    int pos = umNoh->numElementos - 1;
    while (pos >= 0 and primeiraMenor(itemPromovido.key, umNoh->itens[pos].key)){
        umNoh->itens[pos+1] = umNoh->itens[pos];
        umNoh->filhos[pos+2] = umNoh->filhos[pos+1];
        pos--;
    }
    umNoh->itens[pos+1] = itemPromovido;
    umNoh->filhos[pos+2] = novo;
    umNoh->numElementos++;
}

void ArvoreBplus::insere(chave umItem) {
    if (raiz == NULL) {
        raiz = new noh();
        raiz->folha = true;
        raiz->itens[0] = umItem;
        raiz->numElementos = 1;
    } else {
        chave itemPromovido;
        noh* novo = insereAux(raiz,umItem,itemPromovido);
        if (novo != NULL){
            noh* antiga = raiz;
            raiz = new noh();
            raiz->itens[0] = itemPromovido;
            raiz->numElementos = 1;
            raiz->filhos[0] = antiga;
            raiz->filhos[1] = novo;
        }
    }
}

noh* ArvoreBplus::insereAux(noh* umNoh, chave umItem, chave &itemPromovido){
    if (umNoh->folha){
        if (umNoh->numElementos < CAP_PACOTE){
            insereFolhaNaoCheio(umNoh, umItem);
            // itemPromovido = 0;
            return NULL;
        } else {
            insereFolhaNaoCheio(umNoh,umItem);
            noh* novo = divide(umNoh, itemPromovido);
            return novo;
        }
    } else {
        int pos = umNoh->numElementos - 1;
        while ((pos >= 0) and (primeiraMenor(umItem.key, umNoh->itens[pos].key))){
            pos--;
        }
        noh* aux = insereAux(umNoh->filhos[pos+1], umItem, itemPromovido);
        if (aux != NULL){
            if (umNoh->numElementos < CAP_PACOTE){
                insereItermediarioNaoCheio(umNoh,aux,itemPromovido);
                return NULL;
            } else {
                chave itemPf = itemPromovido;
                insereItermediarioNaoCheio(umNoh, aux, itemPf);
                noh* novo = divide(umNoh, itemPromovido);

                return novo;
            }
        }
        return NULL;
    }
}

void ArvoreBplus::percorreEmOrdem() {
    percorreEmOrdemAux(raiz,0);
    cout<< endl;
}

void ArvoreBplus::percorreEmOrdemAux(noh* umNoh, int nivel) {
    int i;
    for (i = 0; i < umNoh->numElementos - 1; i++) {
        // se nó não é folha, imprima os dados do filho i
        // antes de imprimir o item i
        if (not umNoh->folha) {
            percorreEmOrdemAux(umNoh->filhos[i], nivel+1);
        }
        cout << umNoh->itens[i].key << '/' << nivel << ' ';
    }

    // Imprima os dados do último filho
    if (not umNoh->folha) {
        percorreEmOrdemAux(umNoh->filhos[i], nivel+1);
    }
}

void ArvoreBplus::imprimirPelaArvoreAux(noh *umNoh, int espaco){
    int i;
    for(int i=0; i<(espaco-1)*5; i++) {
        if(i % 5 == 0)
            cout << "│";
        else
            cout << " ";
    }
    if(umNoh!=raiz){
        if(umNoh->filhos[0] == NULL)
            cout << "└────";
        else
            cout << "├────";
    }

    for(i=0; i<umNoh->numElementos-1; i++){
        if(umNoh->filhos[0] == NULL) cout << ".";
        cout << umNoh->itens[i].key <<" " ;

    }
     if(umNoh->filhos[0] == NULL) cout << ".";
    cout << umNoh->itens[i].key << "" << endl;
    espaco++;
    for(int i=0; i<umNoh->numElementos+1; i++){
        if(!umNoh->folha) {
            imprimirPelaArvoreAux(umNoh->filhos[i], espaco);
        }
    }

}

//imprime a arvore da raiz aos noh's folhas
void ArvoreBplus::imprimirPelaArvore(){
    if(raiz == NULL){
        cout << "Arvore B+ vazia!" << endl;
    }else{
        imprimirPelaArvoreAux(raiz, 0);
    }
}

bool primeiraMenor(chave chave1, chave chave2){
    int i;
    for (i = 0; chave1.key[i] != '\0' && chave2.key[i] != '\0'; i++){
        //assim que uma letra seja diferente
        if (chave1.key[i] != chave2.key[i]){
            //retorna -1 se a primeira for menor ou 1 caso contrário
            return chave1.key[i] < chave2.key[i] ? true : false;
        }
    }

    if(chave1.key[i] - chave2.key[i] < 0){
        return false;
    }

    return true;
}

// =========================== Programa ================================
int main() {
    ArvoreBplus* B = new ArvoreBplus;

    char opcao;
    chave valor;

    do {
        cin >> opcao;
        if (opcao == 'i') {
            cin >> valor.key;
            B->insere(valor);
        } else if(opcao == 'e') {
            B->imprimirPelaArvore();
        }
    } while(opcao != 'q');


    delete B;

    return 0;
}
