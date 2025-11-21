#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definicoes e Constantes
#define MAX_PAISES 5
#define MAX_NOME 50
#define MAX_COR 15

// Definição da Struct 
struct Territorio
{
    char nome [MAX_NOME];
    char cor [MAX_COR];
    int tropas;
};

// Limpa o Buffer
void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Função Para Ataques
void atacar(struct Territorio *atacante, struct Territorio *defensor){
    printf("\n--- Inicio do Ataque ---\n");
    printf("%s (Atacante) vs %s (Defensor)\n", atacante->nome, defensor->nome);

    //Rola os Dados
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    //Mostra e faz a verificação de quem ganhou o duelo
    printf("Dados: Atacante [%d] x Defensor [%d]\n", dadoAtacante,dadoDefensor);
    if (dadoAtacante > dadoDefensor){
        printf("Vitoria do Atacante!\n");
        strcpy(defensor->cor, atacante->cor);
        int tropasMovidas = atacante->tropas /2;
        defensor->tropas = tropasMovidas;
        atacante->tropas = atacante->tropas - tropasMovidas;

        printf("O territorio agora pertence a cor %s!\n", atacante->cor);
    } else {
        printf("Defesa segurou! O Atacante perdeu tropas. \n");
        if (atacante->tropas > 0){
            atacante->tropas--;
        }
    }
}

//Função Principal
int main(){
    //Define a semente para geração de números aleatórios
    srand(time(NULL));
    //Alocação Dinâmica do vetor de territórios
    struct Territorio *paises;
    paises = (struct Territorio *) calloc(MAX_PAISES, sizeof(struct Territorio));

    //Verificação de Segurança
    if (paises == NULL){
        printf("Erro: Falha ao Alocar Memória.\n");
        return 1;
    }

    //Variaveis de Controle
    int totalPaises = 0;
    int opcaoMenu;
    do
    {
        //Menu Para Escolha das Opções
        printf("=================================\n");
        printf("         WAR ESTRUTURADO         \n");
        printf("=================================\n");
        printf("1 - Cadastrar Territórios (Limite %d)\n", MAX_PAISES);
        printf("2 - Mostrar todos os territórios\n");
        printf("3 - Realizar Ataques\n");
        printf("9 - Sair\n");
        printf("---------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoMenu);
        limparBuffer();

        switch (opcaoMenu)
        {
        case 1: //Cadastro de Países
            printf("--- Cadastro de Novo País ---\n\n");
            if (totalPaises < MAX_PAISES){
                printf("Digite o nome do País %d: ", totalPaises + 1 );
                fgets(paises[totalPaises].nome, MAX_NOME,stdin);
                paises[totalPaises].nome[strcspn(paises[totalPaises].nome, "\r\n")] = 0;

                printf("Digite a cor do País: ");
                fgets(paises[totalPaises].cor, MAX_COR, stdin);
                paises[totalPaises].cor[strcspn(paises[totalPaises].cor, "\r\n")] = 0;

                printf("Digite a Quantidade de Tropas nesse País: ");
                scanf("%d", &paises[totalPaises].tropas);
                limparBuffer();
                totalPaises++;
                printf("\nPaís Cadastrado com Sucesso!\n");
            } else {
                printf("Número Máximo de Cadastro Atingido!\n");
            }
            printf("\nPressione Enter para continuar...");
            getchar();
            break;

        case 2: //Lista dos Países Cadastrados
            printf("--- Lista de Países Cadastrados ---\n\n");
            if (totalPaises == 0){
                printf("Nenhum país cadastrado!\n");
            } else {
                for (int i = 0; i < totalPaises; i++){
                    printf("---------------------------------\n");
                    printf("País %d\n", i + 1);
                    printf("NOME: %s\n", paises[i].nome);
                    printf("COR: %s\n", paises[i].cor);
                    printf("TROPAS: %d\n\n", paises[i].tropas);
                }
                printf("---------------------------------\n");
            }
            printf("\nPressione Enter para continuar...");
            getchar();
            break;
        
        case 3: //Sistema de Ataques
            if (totalPaises < 2) {
                printf("Erro: Precisa no mínimo de 2 países cadastrados!\n");
            } else {
                int atacante = rand() % totalPaises;
                int defensor;
                do
                {
                    defensor = rand() % totalPaises;
                } while (atacante == defensor);
                atacar(&paises[atacante], &paises[defensor]);
                }
            printf("\nPressione Enter para continuar...");
            getchar();
            break;

        case 9: //Sair
            printf("Fechando o jogo...\n");
            break;

        default: //Sistema para Escolha Erradas
            printf("\nOpção Inválida! Escolha uma das opções acima: \n");
            break;
        }
    } while (opcaoMenu != 9); //Sai do Programa

    //Libera a memória alocada dinamicamente para evitar vazamentos
    free(paises);
    return 0;
}