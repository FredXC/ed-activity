/* Sequence Set - Arquivo de Configuração
 * (tipo de elemento armazenado, tamanho do pacote, etc.)
 *
 * by Joukim, Fevereiro de 2021 - Estrutura de Dados (GCC216)
 * Caracteristicas desta implementação - fevereiro de 2021:
 * -> usa chave/valor como dado de exemplo, mas que pode
 * -> ser trocado com facilidade, usando typedef
 * ->
 * -> tamanho máximo e mínimo do pacote definido por
 * -> constantes (CAP_PACOTE e MIN_PACOTE)
 */

using namespace std;

struct elemento {
    char tipo[12];
    char descricao[36]; // utilizar este campo como chave
    char medida[18];
    unsigned peso;
    unsigned calorias;
};

typedef elemento dado; // a arvore guarda informacoes do tipo Dado
typedef char tipoChave[36]; // tipo da chave usada na comparação

// capacidade máxima e mínima do pacote
const unsigned MIN_PACOTE = 4;

// posição do elemento do meio do pacote
const unsigned POS_MEIO = 4;

// posição inválida no disco
const int POS_INVALIDA = -1;
