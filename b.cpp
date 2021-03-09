// Árvore 2-3-4
// (Árvore B em memória, com nós com capacidade para 2, 3 ou 4 filhos)
// Estruturas de Dados - 2018/2
// Código by Joukim

#include <iostream>

using namespace std;

// constantes para verificação
const int CAP_PACOTE = 8;


// posição do elemento do meio (o que sobe para página pai em caso de estouro
const int POS_MEIO = 4;
typedef float dado;

class Noh {
friend class ArvoreBplus;
private:
    bool folha;
    unsigned numElementos; // número de itens armazenadas no nó
    dado itens[CAP_PACOTE+1];
    Noh* filhos[CAP_PACOTE+1];
    Noh* pai;
public:
    Noh();
    ~Noh();
};

Noh::Noh() {
    numElementos = 0;
    folha = false;
    for (int i = 0; i < CAP_PACOTE+1; i++) {
        filhos[i] = NULL;
    }
}

Noh::~Noh() {
    for (int i = 0; i < numElementos+1; i++) {
        delete filhos[i];
    }
}

class ArvoreBplus {
private:
    Noh* raiz;
    void percorreEmOrdemAux(Noh* atual, int nivel);
public:
    ArvoreBplus() { raiz = NULL; }
    ~ArvoreBplus() { delete raiz; }
    // código não implementado, sua tarefa é implementá-lo!
    void insereFolhaNaoCheio(Noh* umNoh, dado umItem);
    Noh* divide (Noh* umNoh, dado &itemPromovido);
    void insereItermediarioNaoCheio(Noh* umNoh, Noh* novo, dado &itemPromovido);
    Noh* insereAux(Noh* umNoh, dado umItem, dado &itemPromovido);
    void insere(dado umItem);
    // percorrimento (impressão)
    void percorreEmOrdem();
    void imprimirPelaArvoreAux(Noh *umNoh, int espaco);
    void imprimirPelaArvore();
};

void ArvoreBplus::insereFolhaNaoCheio(Noh* umNoh, dado umItem){
    int pos = umNoh->numElementos - 1;
    cout <<"pos: "<< pos << endl;
    while ((pos >= 0) and (umNoh->itens[pos] > umItem)){
        cout << "pos+1" << umNoh->itens[pos+1] << " pos"<<  umNoh->itens[pos] << endl;
        umNoh->itens[pos+1] = umNoh->itens[pos];
        pos--;
    }
    cout << "Fora do while" << endl;
    cout <<"pos+1  " << umNoh->itens[pos+1] << " um item  "<<  umItem<< endl;
    umNoh->itens[pos+1] = umItem;
    umNoh->numElementos++;
}

Noh* ArvoreBplus::divide(Noh* umNoh, dado &itemPromovido){
    itemPromovido = umNoh->itens[POS_MEIO];
    cout << itemPromovido << endl;
    Noh* novo = new Noh();
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
        cout << "Mostrando filhos: " << endl;
        for (int i = 0; i < POS_MEIO+1; i++){
            cout << novo->filhos[i] << endl;
        }
    }
    return novo;

}

void ArvoreBplus::insereItermediarioNaoCheio(Noh* umNoh, Noh* novo, dado &itemPromovido){
    int pos = umNoh->numElementos - 1;
    while (pos >= 0 and umNoh->itens[pos] > itemPromovido){
        umNoh->itens[pos+1] = umNoh->itens[pos];
        umNoh->filhos[pos+2] = umNoh->filhos[pos+1];
        pos--;
    }
    umNoh->itens[pos+1] = itemPromovido;
    umNoh->filhos[pos+2] = novo;
    umNoh->numElementos++;
}

void ArvoreBplus::insere(dado umItem) {
    if (raiz == NULL) {
        raiz = new Noh();
        raiz->folha = true;
        raiz->itens[0] = umItem;
        raiz->numElementos = 1;
    } else {
        dado itemPromovido = 0;
        Noh* novo = insereAux(raiz,umItem,itemPromovido);
        if (novo != NULL){
            Noh* antiga = raiz;
            raiz = new Noh();
            raiz->itens[0] = itemPromovido;
            raiz->numElementos = 1;
            raiz->filhos[0] = antiga;
            raiz->filhos[1] = novo;
        }
    }
}

Noh* ArvoreBplus::insereAux(Noh* umNoh, dado umItem, dado &itemPromovido){
    if (umNoh->folha){
        if (umNoh->numElementos < CAP_PACOTE){
            insereFolhaNaoCheio(umNoh, umItem);
            itemPromovido = 0;
            return NULL;
        } else {
            insereFolhaNaoCheio(umNoh,umItem);
            for(int i = 0; i < umNoh->numElementos; i++){
                cout << umNoh->itens[i] << " " << endl;
            }
            Noh* novo = divide(umNoh, itemPromovido);
            return novo;
        }
    } else {
        int pos = umNoh->numElementos - 1;
        while ((pos >= 0) and (umNoh->itens[pos] > umItem)){
            pos--;
        }
        Noh* aux = insereAux(umNoh->filhos[pos+1], umItem, itemPromovido);
        if (aux != NULL){
            if (umNoh->numElementos < CAP_PACOTE){
                insereItermediarioNaoCheio(umNoh,aux,itemPromovido);
                return NULL;
            } else {
                dado itemPf = itemPromovido;
                insereItermediarioNaoCheio(umNoh, aux, itemPf);
                Noh* novo = divide(umNoh, itemPromovido);

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

void ArvoreBplus::percorreEmOrdemAux(Noh* umNoh, int nivel) {
    int i;
    for (i = 0; i < umNoh->numElementos - 1; i++) {
        // se nó não é folha, imprima os dados do filho i
        // antes de imprimir o item i
        if (not umNoh->folha) {
            percorreEmOrdemAux(umNoh->filhos[i], nivel+1);
        }
        cout << umNoh->itens[i] << '/' << nivel << ' ';
    }

    // Imprima os dados do último filho
    if (not umNoh->folha) {
        percorreEmOrdemAux(umNoh->filhos[i], nivel+1);
    }
}

void ArvoreBplus::imprimirPelaArvoreAux(Noh *umNoh, int espaco){
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
        cout << umNoh->itens[i] <<" " ;

    }
     if(umNoh->filhos[0] == NULL) cout << ".";
    cout << umNoh->itens[i] << "" << endl;
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


// =========================== Programa ================================
int main() {
    ArvoreBplus* B = new ArvoreBplus;

    char opcao;
    float valor;

    do {
        cin >> opcao;
        if (opcao == 'i') {
            cin >> valor;
            B->insere(valor);
        } else if(opcao == 'e') {
            B->imprimirPelaArvore();
        }
    } while(opcao != 'q');


    delete B;

    return 0;
}
