#include <iostream>
#include "sequenceset.hpp"

using namespace std;

int main() {
    sequenceset meuSeqSet("teste.dat");
    dado umDado;
    tipoChave umaChave;
    char operacao;

    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // inserir
                    cin >> umDado.tipo >> umDado.descricao >> umDado.medida >> umDado.peso >> umDado.calorias;
                    meuSeqSet.inserirDado(umDado);
                    break;
                case 'b': // buscar
                    cin >> umaChave;
                    umDado = meuSeqSet.buscar(umaChave);
                    cout << "Busca: "<< umDado.descricao << "/" << umDado.tipo << "/"
                        << umDado.medida << "/" << umDado.peso << "/" << umDado.calorias << endl;
                    break;
                case 'p': // mostrar estrutura
                    meuSeqSet.imprimir();
                    break;
                case 'd': // mostrar estrutura
                    meuSeqSet.depurar();
                    break;
                case 's': // sair
                    // será tratado no while
                    break;
                default:
                    cout << "Opção inválida!" << endl;
            }
        } catch (runtime_error& e) {
            cerr << e.what() << endl;
        }
    } while (operacao != 's');

    return 0;
}
