#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5

//Molde da Peça
typedef struct {
    char tipo;
    int id;
} Peca;

//Definição da Fila
typedef struct {
    Peca itens[MAX_FILA];
    int inicio;
    int fim;
    int quantidade;
} FilaCircular;

int contadorID = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pressioneEnter(){
    printf("\n[Enter] para continuar...");
    getchar();
}

//Função que gera peças pro nosso jogo.
Peca gerarpeca(){
    Peca novaPeca;
    char tipos[] = {'I','O','T','L'};
    int indice = rand() % 4;

    novaPeca.tipo = tipos[indice];
    novaPeca.id = contadorID++;
    return novaPeca;
}

//Inicializa a Fila com as peças
void iniciarFila(FilaCircular *fila){
    fila->inicio = 0;
    fila->fim = 0;
    fila->quantidade = 0;

    printf(">>> Iniciando Tetris");
    for (int i = 0; i < MAX_FILA; i++){
        Peca novaPeca = gerarpeca();
        fila->itens[fila->fim] = novaPeca;
        fila->fim++;
        fila->quantidade++;
    }
} 

//Insere Novas peças a nossa fila
void inserirNovaPeca(FilaCircular *fila){
    if (fila->quantidade == MAX_FILA){
        printf("\n[ERRO] A Fila de peças está cheia!!\n");
        return;
    }

    Peca novaPeca = gerarpeca();
    fila->itens[fila->fim] = novaPeca;
    fila->fim = (fila->fim + 1) % MAX_FILA; // O Fim da fila é 4, somamos 1 para ficar 5, o resto da divisão de 5 por MAX_FILA(5),
    //É 0, fazendo voltar pro começo.
    fila->quantidade++;
    printf("[Nova] Peca [%c %d] entrou na fila.\n", novaPeca.tipo, novaPeca.id);
}

//Funcao quando o jogador quiser jogar a peça
void jogarPeca(FilaCircular*fila){
    if (fila->quantidade == 0){
        printf("\n[ERRO] Não há peça para jogar\n");
        return;
    }

    Peca pecaJogada = fila->itens[fila->inicio];
    printf("\n==================================\n");
    printf("    JOGANDO PECA: [%c #%d]       \n", pecaJogada.tipo, pecaJogada.id);
    printf("==================================\n");

    fila->inicio = (fila->inicio + 1) % MAX_FILA;
    fila->quantidade--;
}

//Mostra a fila de peças
void exibirFila(FilaCircular *fila){
    printf("\n--- PROXIMAS PECAS [%d/%d] ---\n", fila->quantidade, MAX_FILA);
    if (fila->quantidade == 0){
        printf("[VAZIO]\n");
    } else {
        int i = fila->inicio;
        for (int contador = 0; contador < fila->quantidade;contador++){
            printf("[%c %d] ", fila->itens[i].tipo, fila->itens[i].id);
            i = (i + 1) % MAX_FILA;
        }
        printf("\n");
        printf("------------------------------\n");
        printf("Frente (Inicio): %d | Tras (Fim): %d\n", fila->inicio, fila->fim);
    }
}

// --- MAIN ---
int main() {
    srand(time(NULL)); // Semente aleatória
    FilaCircular filaPecas;
    int opcao;

    // 1. Inicializa (Preenche a fila inicial)
    iniciarFila(&filaPecas);

    do {        
        printf("=== TETRIS STACK: CONTROLE DE FILA ===\n");
        exibirFila(&filaPecas);
        
        printf("\nOpcoes de acao:\n");
        printf("1 - Jogar peca (Dequeue)\n");
        printf("2 - Inserir nova peca (Enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                jogarPeca(&filaPecas);
                pressioneEnter();
                break;
            case 2:
                inserirNovaPeca(&filaPecas);
                pressioneEnter();
                break;
            case 0:
                printf("Encerrando Tetris Stack...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                pressioneEnter();
        }

    } while (opcao != 0);

    return 0;
}