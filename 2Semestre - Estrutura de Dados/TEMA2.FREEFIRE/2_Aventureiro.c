#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 30
#define MAX_TIPO 20
#define TAM_MAX 10

/*
 DIFERENÇA entre VETOR e LISTA
 MochilaVetor (Lista Sequencial):
 Acesso direto e imediato via índice (ex: itens[5]).
 
 MochilaLista (Lista Encadeada):
 Cada 'No' está em um lugar diferente da RAM. o Acesso é Sequencial.
 Para chegar no item 5, precisa passar pelo 1, 2, 3 e 4.
 */

//Aqui definimos o modelo do Item e da Mochila usando Structs
typedef struct {
    char nome [MAX_NOME];
    char tipo [MAX_TIPO];
    int quantidade;
} Item;

//Mochila na estrutura de vetor (Lista Estática)
typedef struct {
    Item itens [TAM_MAX];
    int total;
} MochilaVetor;

//Estrutura do Nó para Lista Encadeada
typedef struct No {
    Item dado;
    struct No *proximo;
} No;

//Mochila na estrutura de lista encadeada
typedef struct {
    No *inicio;
    int total;
} MochilaLista;

//Função que limpa o buffer de scanf
void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pressioneEnter(){
    printf("Pressione Enter...");
    getchar();
}

void ordenarVetor(MochilaVetor *mochila){
    int minIndex;
    Item temp;
    for (int i = 0; i < mochila->total; i++){
        minIndex = i;
        for(int j = i + 1; j < mochila->total; j++){
            if (strcmp(mochila->itens[j].nome, mochila->itens[minIndex].nome) < 0){
                minIndex = j;
            }
        }
        if (minIndex != i){
            temp = mochila->itens[i];
            mochila->itens[i] = mochila->itens[minIndex];
            mochila->itens[minIndex] = temp;
        }
    }
}


/*
 É muito rápida (O(1)) porque apenas escrevemos na primeira posição livre.
 Porém, exige verificação de limite (TAM_MAX) para evitar "Overflow".
 A chamada para 'ordenarVetor' mantém a integridade para a Busca Binária.
 */
void adicionarItemEstatico(MochilaVetor *mochila, char nome[], char tipo[], int qtd){
    strcpy(mochila->itens[mochila->total].nome, nome);
    strcpy(mochila->itens[mochila->total].tipo, tipo);
    mochila->itens[mochila->total].quantidade = qtd;

    mochila->total++;
    printf("\n[SUCESSO] Item guardado na mochila!\n");
    if(mochila->total >= 2){
        ordenarVetor(mochila);
        printf("[AUTO] Mochila reordenada automaticamente.\n");
    }
}

/*
 Removemos o item buscado, porém esse índice fica vazio, então movemos os itens da frente
 uma casa para trás.
 */
void removerItemEstatico(MochilaVetor *mochila, char nomeBuscado[]){
    int indice = -1;
    for (int i = 0; i < mochila->total; i++){
        if(strcmp(mochila->itens[i].nome, nomeBuscado) == 0){
            indice = i;
            break;
        }
    }
    if (indice == -1){
        printf("\n[ERRO] Item '%s' nao encontrado.\n", nomeBuscado);    
    } else {
        for (int j = indice; j < mochila->total -1; j++){
            mochila->itens[j] = mochila->itens[j+1];
        }
        mochila->total--;
        printf("\n[SUCESSO] Item removido da mochila!\n");
    }
}

//Lista todos os itens que estão dentro do vetor
void listarItensEstatico(MochilaVetor *mochila){
    if (mochila->total == 0){
        printf("\n[ERRO] Mochila sem itens.\n");
    } else {
        printf("              MOCHILA\n");
        printf("          Total de Itens %d/10\n\n",mochila->total);
        printf("%-3s| %-30s | %-20s | x%s\n","ID","NOME","TIPO","QTD");
        printf("--------------------------------------------------------------------\n");
        for(int i = 0; i < mochila->total; i++){
            printf("%-3d| %-30s | %-20s | x%d\n", i + 1, mochila->itens[i].nome, mochila->itens[i].tipo, mochila->itens[i].quantidade);    
            }
        printf("\n\n");
        pressioneEnter();
    }
}

//Busca Sequencial: Testa um por um, índice por índice
int buscarItensEstataticoSequencial(MochilaVetor *mochila, char nomeBuscado[]){
    int itemEncontrado = 0;
    int comparacoes = 0;
    for (int i = 0; i < mochila->total; i++){
        comparacoes++;

        if (strcmp(mochila->itens[i].nome, nomeBuscado) == 0){
            printf("\n[ITEM ENCONTRADO]\n", i + 1);
            printf("Nome: %s\n", mochila->itens[i].nome);
            printf("Tipo: %s\n", mochila->itens[i].tipo);
            printf("Qtd:  %d\n\n", mochila->itens[i].quantidade);
            itemEncontrado = 1;
            break;
        }
    }
    if (itemEncontrado == 0){
        printf("[!] Item nao encontrado na mochila.\n");
    }
    return comparacoes;
}

//Busca Binária: Para funcionar organizamos o vetor, assim ele ve o valor do meio do vetor e faz a busca se está antes ou depois
int buscarItensEstaticoBinario(MochilaVetor *mochila, char nomeBuscado[]){
    int inicio = 0;
    int fim = mochila->total -1;
    int meio;
    int comparacoes = 0;
    int encontrou = 0;

    while (inicio <= fim)
    {
        comparacoes++;
        meio = (inicio + fim) / 2;
        int resultado = strcmp(mochila->itens[meio].nome, nomeBuscado);
        if(resultado == 0){
            printf("\n[ENCONTRADO] Slot %d (Indice %d)\n", meio + 1, meio);
            printf("Nome: %s | Tipo: %s | Qtd: %d\n", 
                   mochila->itens[meio].nome, 
                   mochila->itens[meio].tipo, 
                   mochila->itens[meio].quantidade);
            encontrou = 1;
            break; // Sai do loop
        } else {
            if (resultado < 0){
                inicio = meio + 1;
            } else {
                fim = meio - 1;
            }
        }
    }
    if (!encontrou){
        printf("[!] Item nao encontrado.\n");
    }
    return comparacoes;
}

void listaEstatica(){
    int opcao;
    MochilaVetor bag;
    bag.total = 0;

    char nomeTemp [MAX_NOME];
    char tipoTemp [MAX_TIPO];
    int qtdTemp;

    do {
        printf("----------------------------\n");
        printf("===== MOCHILA FREEFIRE =====\n");
        printf("   *** lista estática ***\n");
        printf("----------------------------\n");
        printf("   Itens na Mochila %d/10\n\n",bag.total);
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("0. VOLTAR\n");
        printf("----------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case 1:
            if (bag.total == TAM_MAX){
                printf("\n[ERRO] Mochila Cheia! Remova Algo Antes.\n");
            } else {
                printf("\n--- ADICIONAR LOOT ---\n");
                printf("Nome: ");
                fgets(nomeTemp, MAX_NOME, stdin);
                nomeTemp[strcspn(nomeTemp, "\n")] = 0;

                printf("Tipo: ");
                fgets(tipoTemp, MAX_TIPO, stdin);
                tipoTemp[strcspn(tipoTemp, "\n")] = 0;

                printf("Quantidade: ");
                scanf("%d", &qtdTemp);
                limparBuffer();

                adicionarItemEstatico(&bag, nomeTemp, tipoTemp, qtdTemp);
                listarItensEstatico(&bag);
            }
            opcao = -1;
            break;
        
        case 2:
            if(bag.total == 0){
                printf("\n[ERRO] Mochila sem itens.\n");
            } else {
                printf("--- DROPAR ITEM ---\n");
                printf("Nome do Item: ");
                fgets(nomeTemp,30,stdin);
                nomeTemp[strcspn(nomeTemp, "\n")] = 0;
                removerItemEstatico(&bag,nomeTemp);    
            }
            pressioneEnter();
            opcao = -1;
            break;
        
        case 3:
            listarItensEstatico(&bag);
            opcao = -1;
            break;

        case 4:
            if(bag.total == 0){
                printf("\n[ERRO] Mochila sem itens.\n");
                pressioneEnter();
                opcao = -1;
                break;
            } else {
                printf("\n--- Buscar Loot ---\n");
                printf("Item Buscado: ");
                fgets(nomeTemp, 30, stdin);
                nomeTemp[strcspn(nomeTemp, "\n")] = 0;

                printf("       BUSCANDO ITENS\n");
                printf("----------------------------\n");
                int comparacaoSequencial = buscarItensEstataticoSequencial(&bag, nomeTemp);
                int comparacaoBinaria = buscarItensEstaticoBinario(&bag, nomeTemp);

                printf("\n=======================================\n");
                printf("          RESULTADO COMPARACOES          \n");
                printf("=======================================\n");
                printf("Busca SEQUENCIAL: %d comparacoes\n", comparacaoSequencial);
                printf("Busca BINARIA:    %d comparacoes\n", comparacaoBinaria);
                printf("---------------------------------------\n");
            }
            pressioneEnter();
            opcao = -1;
            break;

        default:
            break;
        }
    } while (opcao != 0);
}

/*
 Inserção Dinâmica: Não existe limite fixo.
 Usamos 'malloc' para pedir memória ao sistema operacional em tempo de execução (Heap).
 Criamos um novo No e conectamos ao ponteiro proximo.
 */
void adicionarItemLista(MochilaLista *lista,char nome[], char tipo[], int qtd){
    No *novoNo = (No*) malloc(sizeof(No));
    if(novoNo == NULL){
        printf("[ERRO CRITICO] Memoria cheia!\n");
        return;
    }
    strcpy(novoNo->dado.nome, nome); 
    strcpy(novoNo->dado.tipo, tipo);
    novoNo->dado.quantidade = qtd;
    novoNo->proximo = NULL;

    if (lista->inicio == NULL){
        lista->inicio = novoNo;
    } else {
        No *atual = lista->inicio;
        while(atual->proximo != NULL){
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }
    lista->total++;
    printf("\n[SUCESSO] Item adicionado na Lista Dinamica!\n");
}

/*
 Removemos o item buscado e não precisamos mover dados (Shift Left). Apenas "refazemos as ligações".
 O nó ANTERIOR aponta para o PRÓXIMO, pulando o nó atual.
 */
void removerItemLista(MochilaLista *lista, char nomeBuscado[]){
    No *atual = lista->inicio;
    No *anterior = NULL;

    while(atual != NULL){
        if(strcmp(atual->dado.nome, nomeBuscado) == 0){
            if(anterior == NULL){
                lista->inicio = atual->proximo;
            } else {
                anterior->proximo = atual -> proximo;
            }
            free(atual);
            lista->total--;
            printf("\n[SUCESSO] Item '%s' removido e memoria liberada!\n", nomeBuscado);
            return;
        }
        anterior = atual;
        atual = atual -> proximo;
    }
    printf("\n[ERRO] Item nao encontrado.\n");
}

//Lista todos os itens que estão na memória
void listarItensLista(MochilaLista *lista){
    printf("              LISTA ENCADEADA\n");
    printf("%-3s| %-30s | %-20s | x%s\n","ID","NOME","TIPO","QTD");
    printf("--------------------------------------------------------------------\n");
    No *atual = lista->inicio;
    int i = 1;
    while (atual != NULL){
        printf("%-3d| %-30s | %-20s | x%d\n", i, atual->dado.nome, atual->dado.tipo, atual->dado.quantidade);
        atual = atual->proximo;
        i++;
    }
    printf("\nTotal de Nos na memoria: %d\n", lista->total);
    pressioneEnter();
}

//Buscamos o item através de ponteiros
void buscarItemLista(MochilaLista *lista, char nomeBuscado[]){
    No *atual = lista->inicio;
    int encontrou = 0;
    int comparacoes = 0;
    printf("\n--- BUSCA NA LISTA (Sequencial) ---\n");
    while (atual != NULL){
        comparacoes++;
        if(strcmp(atual->dado.nome, nomeBuscado) == 0){
            printf("\n[ENCONTRADO]\n");
            printf("Nome: %s |Tipo: %s | Qtd: %d\n", atual->dado.nome,atual->dado.tipo, atual->dado.quantidade);
            encontrou = 1;
            break;
        }
        atual = atual->proximo;
    }
    if(!encontrou) printf("[!] Item nao encontrado.\n");
    
    printf("--------------------------------\n");
    printf("Comparacoes realizadas: %d\n", comparacoes);
    printf("--------------------------------\n");
}

void listaEncadeada(){
    MochilaLista minhaLista;
    minhaLista.inicio = NULL;
    minhaLista.total = 0;

    int opcao;
    char nomeTemp[MAX_NOME], tipoTemp[MAX_TIPO];
    int qtdTemp;

    do  {
        printf("----------------------------\n");
        printf("===== MOCHILA FREEFIRE =====\n");
        printf("   *** lista encadeada ***\n");
        printf("----------------------------\n");
        printf("   Itens na Mochila %d/10\n\n",minhaLista.total);
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case 1:
            printf("\n--- ADICIONAR LOOT ---\n");
            printf("Nome: ");
            fgets(nomeTemp, MAX_NOME, stdin);
            nomeTemp[strcspn(nomeTemp, "\n")] = 0;

            printf("Tipo: ");
            fgets(tipoTemp, MAX_TIPO, stdin);
            tipoTemp[strcspn(tipoTemp, "\n")] = 0;

            printf("Quantidade: ");
            scanf("%d", &qtdTemp);
            limparBuffer();
            adicionarItemLista(&minhaLista, nomeTemp, tipoTemp, qtdTemp);
            pressioneEnter();
            break;

        case 2:
            if(minhaLista.inicio == NULL){
                printf("\n[AVISO] Lista Vazia.\n");
                pressioneEnter();
                break;
            } else {
                printf("\n--- REMOVER LOOT ---\n");
                printf("Nome: ");
                fgets(nomeTemp, MAX_NOME, stdin);
                nomeTemp[strcspn(nomeTemp, "\n")] = 0;
                removerItemLista(&minhaLista, nomeTemp);
                pressioneEnter();
                break;
            }

        case 3:
            if(minhaLista.inicio == NULL){
                printf("\n[AVISO] Lista Vazia.\n");
                pressioneEnter();
                break;
            } else {
                listarItensLista(&minhaLista);
                pressioneEnter();
                break;
            }
        
        case 4:
            if(minhaLista.inicio == NULL){
                printf("\n[AVISO] Lista Vazia.\n");
            } else {
                printf("\n--- BUSCAR LOOT ---\n");
                printf("Nome: ");
                fgets(nomeTemp, MAX_NOME, stdin);
                nomeTemp[strcspn(nomeTemp, "\n")] = 0;

                buscarItemLista(&minhaLista, nomeTemp);
            }
            pressioneEnter();
            break;

        case 0:
            No *atual = minhaLista.inicio;
            while (atual != NULL){
                No *temp = atual;
                atual = atual->proximo;
                free (temp);
            }
            printf("Memoria liberada.\n");
            pressioneEnter();
            break;
        }      

    } while (opcao != 0); 
}

int main(){
    int opcao;
    do{
        //Menu Principal
        printf("-----------------------------\n");
        printf("=== MANIPULAÇÃO DE LISTAS ===\n");
        printf("-----------------------------\n");
        printf("1. Lista Estática\n");
        printf("2. Lista Encadeada \n");
        printf("0. SAIR\n");
        printf("----------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao){
            case 1:
                listaEstatica();
                break;

            case 2:
                listaEncadeada();
                break;

            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                printf("Pressione Enter...");
                getchar();
                opcao = -1;
                break;
            }
    } while (opcao != 0);
    return 0;
}