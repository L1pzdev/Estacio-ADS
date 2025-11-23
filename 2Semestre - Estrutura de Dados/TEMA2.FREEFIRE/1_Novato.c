#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Constante Global
#define TAM_MAX 10

//Struct contendo Nome, Tipo, Quantidade, Maximo de Itens
typedef struct {
    char nome [30];
    char tipo [20];
    int quantidade;
} Item;

typedef struct {
    Item itens[TAM_MAX];
    int total;
} Mochila;

//Função que limpa o buffer de scanf
void limpaBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função responsável por GRAVAR os dados na memória.
// Recebe a mochila e os dados já validados pela main.
// Copia as strings e o inteiro para a posição correta e incrementa o total.
void adicionarItem(Mochila *bag, char nome[], char tipo[], int qtd){
    strcpy(bag->itens[bag->total].nome,nome);
    strcpy(bag->itens[bag->total].tipo,tipo);
    bag->itens[bag->total].quantidade = qtd;

    bag->total++;
    printf("\n[SUCESSO] Item guardado na mochila!\n");
}

//Funcao para remover item caso encontrarmos dentro da mochila
//Primeiro verifica se existe o item, se existe faz a remoção e depois reajusta a posição dos outros itens do vetor
void removerItem(Mochila *bag, char nomeRemover[]){
    int indice = -1; //Variavel para auxilio na busca dentro da condicao imposta!   
    for (int i = 0; i < bag->total; i++){
        if(strcmp(bag->itens[i].nome, nomeRemover) == 0){
            indice = i; //Se encontrar o nome buscado, passa a posicao/indice dentro do vetor para a variável
            break;
        }
    }
    if (indice == -1){
        printf("\n[ERRO] Item '%s' nao encontrado.\n", nomeRemover);
    } else {
        for (int j = indice; j < bag->total -1; j++){//Começa do indice aonde encontrou o item e vai até o penúltimo item 
            bag->itens[j] = bag->itens[j+1]; //Aqui ele pega o item da frente e copia para o indice de tras
        }
        bag->total--; //Diminui o total de itens, por exemplo, se antes tinhamos 4 agora teremos 3.
        printf("\n[SUCESSO] Item removido da mochila!\n");
    }
}

//Lista todos os itens ja cadastrados dentro da mochila
//Se ela não possuir itens, temos uma mensagem de erro!
//O "-x" onde x é um numero, é para garantir espaço minimo, ficar tudo padronizado.
void listarItens(Mochila *bag){
    if (bag -> total == 0){
        printf("\n[ERRO] Mochila sem itens.\n");
    } else {
        printf("              MOCHILA\n");
        printf("%-3s| %-30s | %-20s | x%s\n","ID","NOME","TIPO","QTD");
        printf("--------------------------------------------------------------------\n");
        for(int i = 0; i < bag->total; i++){
                printf("%-3d| %-30s | %-20s | x%d\n", i + 1, bag->itens[i].nome, bag->itens[i].tipo, bag->itens[i].quantidade);    
            }
        }
}

//Recebe o Nome passado pelo case na main, iniciamos um laço pra percorrer o vetor e descobrir se o item buscado existe dentro da nossa mochila, exibindo na tela os dados do item se encontrado, ou aviso de erro.
void buscarItens(Mochila *bag, char nomeBuscado[]){
    int itemEncontrado = 0; //Variavel que define se encontramos e saimos do loop
    printf("       BUSCANDO ITENS\n");
    printf("----------------------------\n");
    for (int i = 0; i < bag->total; i++){
        if(strcmp(bag->itens[i].nome, nomeBuscado) == 0){
            printf("\n[ITEM ENCONTRADO]\n", i + 1);
            printf("Nome: %s\n", bag->itens[i].nome);
            printf("Tipo: %s\n", bag->itens[i].tipo);
            printf("Qtd:  %d\n", bag->itens[i].quantidade);
            itemEncontrado = 1;
            printf("Pressione Enter...");
            getchar();
        }
    }
    if (itemEncontrado == 0){
        printf("[!] Item nao encontrado na mochila.\n");
        printf("Pressione Enter...");
        getchar();
    }
}

int main(){
    int opcao;
    Mochila bag;
    bag.total = 0;

    //Variaveis de Auxilio para Adicionar ou Buscar Itens
    char nomeTemp[30];
    char tipoTemp[30];
    int qtdTemp;

    do
    {
        //Menu Principal
        printf("----------------------------\n");
        printf("===== MOCHILA FREEFIRE =====\n");
        printf("----------------------------\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("0. SAIR\n");
        printf("----------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limpaBuffer();

        switch (opcao)
        {
        case 1:
        //Se a bag possuir mais de 10 itens, não pode adicionar mais
        //Caso contrario, permite adicionar e passa os argumentos para a função
        //Opcao -1 é utilizado para forçar a opção a mudar, pois se digitarmos 1, ao entrarmos no menu novamente e digitarmos algo como 'abc' ele ficaria guardado com o ultimo valor selecionado.
            if (bag.total >= 10){
                printf("\n[ERRO] Mochila Cheia! Remova Algo Antes.\n");
            } else {              
                printf("\n--- Novo Loot ---\n");
                printf("Nome: ");
                fgets(nomeTemp, 30, stdin);
                nomeTemp[strcspn(nomeTemp, "\n")] = 0;

                printf("Tipo: ");
                fgets(tipoTemp, 30, stdin);
                tipoTemp[strcspn(tipoTemp, "\n")] = 0;

                printf("Quantidade: ");
                scanf("%d", &qtdTemp);
                limpaBuffer();

                adicionarItem(&bag, nomeTemp, tipoTemp, qtdTemp);
                listarItens(&bag);
            }
            printf("Pressione Enter...");
            getchar();
            opcao = -1;
            break;
        
        case 2:
        //Pede o nome do item para remover e envia para a função
            if (bag.total == 0){
                printf("\n[ERRO] Mochila sem itens.\n");
            } else {
                printf("--- DROPAR ITEM ---\n");
                printf("Nome do Item: ");
                fgets(nomeTemp,30,stdin);
                nomeTemp[strcspn(nomeTemp, "\n")] = 0;
                removerItem(&bag,nomeTemp);
            }
            printf("Pressione Enter...");
            getchar();
            opcao = -1;
            break;

        case 3:
        //Chama a função para listar os itens que estão dentro da bag.
            listarItens(&bag);
            printf("Pressione Enter...");
            getchar();
            opcao = -1;
            break;
        
        case 4:
        //Busca itens dentro da mochila, passa o item buscado para a função.
            if (bag.total == 0){
                printf("\n[ERRO] Mochila sem itens.\n");
                printf("Pressione Enter...");
                getchar();
                opcao = -1;
                break;
            } else {
                printf("\n--- Buscar Loot ---\n");
                printf("Item Buscado: ");
                fgets(nomeTemp, 30, stdin);
                nomeTemp[strcspn(nomeTemp, "\n")] = 0;

                buscarItens(&bag, nomeTemp);
            }
            printf("Pressione Enter...");
            getchar();
            opcao = -1;
            break;

        case 0:
            printf("Saindo da Mochila!");
            break;

        default:
            printf("\nComando Inválido!");
            opcao = -1;
            break;
        }
    } while (opcao != 0);
}