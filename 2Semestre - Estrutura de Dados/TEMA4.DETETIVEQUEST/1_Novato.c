#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala{
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Função Criar Sala
//Aloca memória para um novo nó da árvore e define o nome dela

Sala* criarSala(char nome[]){
    Sala *novaSala = (Sala*) malloc(sizeof(Sala));
    if (novaSala == NULL){
        printf("[ERRO] Falha ao alocar memoria para a sala!\n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

//Função que permite a exploração das salas através da árvore.
void explorarSalas(Sala *raiz) {
    Sala *atual = raiz;
    char escolha;

    printf("\n====================================\n");
    printf("      DETECTIVE QUEST: INICIO       \n");
    printf("====================================\n");

    while (atual != NULL) {
        printf("\n------------------------------------\n");
        printf("VOCE ESTA EM: [ %s ]\n", atual->nome);
        printf("------------------------------------\n");

        // VERIFICAÇÃO DE NÓ FOLHA (Fim do caminho)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\n>>> Fim da linha! Este comodo nao tem mais saidas.\n");
            printf(">>> Investigacao concluida nesta rota.\n");
            break; // Sai do loop
        }

        // MOSTRA AS OPÇÕES
        printf("Para onde deseja ir?\n");
        if (atual->esquerda != NULL) printf("[e] Esquerda: %s\n", atual->esquerda->nome);
        if (atual->direita != NULL)  printf("[d] Direita:  %s\n", atual->direita->nome);
        printf("[s] Sair do jogo\n");
        
        printf("Sua escolha: ");
        scanf(" %c", &escolha); // O espaço antes de %c ignora espaços em branco
        limparBuffer();

        // LÓGICA DE MOVIMENTAÇÃO
        if (escolha == 'e' || escolha == 'E') {
            if (atual->esquerda != NULL) {
                printf("...Caminhando para a esquerda...\n");
                atual = atual->esquerda; // O ponteiro avança para o nó da esquerda
            } else {
                printf("[!] Nao ha passagem a esquerda!\n");
            }
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita != NULL) {
                printf("...Caminhando para a direita...\n");
                atual = atual->direita; // O ponteiro avança para o nó da direita
            } else {
                printf("[!] Nao ha passagem a direita!\n");
            }
        } 
        else if (escolha == 's' || escolha == 'S') {
            printf("Saindo da mansao...\n");
            break;
        } 
        else {
            printf("[!] Opcao invalida. Tente novamente.\n");
        }
    }
}

void liberarMapa(Sala *raiz) {
    if (raiz == NULL) return;
    liberarMapa(raiz->esquerda);
    liberarMapa(raiz->direita);
    free(raiz);
}

int main() {
    // Nível 1 (Raiz)
    Sala *mapa = criarSala("Hall de Entrada");

    // Nível 2
    mapa->esquerda = criarSala("Sala de Estar");
    mapa->direita = criarSala("Cozinha");

    // Nível 3 (Conectando na Sala de Estar)
    mapa->esquerda->esquerda = criarSala("Biblioteca"); // Folha
    mapa->esquerda->direita = criarSala("Jardim de Inverno"); // Folha

    // Nível 3 (Conectando na Cozinha)
    mapa->direita->esquerda = criarSala("Despensa"); // Folha
    mapa->direita->direita = criarSala("Porão Escuro"); // Folha

    // 2. INÍCIO DA EXPLORAÇÃO
    explorarSalas(mapa);

    // 3. ENCERRAMENTO
    printf("\nFim do Jogo. Ate a proxima!\n");
    liberarMapa(mapa); // Limpeza de memória

    return 0;
}


/* ESTRUTURA VISUAL DA ÁRVORE:
                [Hall]
                /      \
        [Sala Estar]  [Cozinha]
        /      \      /     \
    [Biblioteca][Jardim][Despensa][Porao]
*/