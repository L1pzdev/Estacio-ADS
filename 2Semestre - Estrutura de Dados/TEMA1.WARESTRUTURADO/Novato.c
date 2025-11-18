#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes Globais
#define MAX_PAIS 5
#define MAX_NOME 30
#define MAX_COR 10

// Definição da Struct 
struct Territorio {
    char nome [MAX_NOME];
    char cor [MAX_COR];
    int tropas;
};

// Limpa o Buffer
void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Função Principal
int main(){
    struct Territorio paises[MAX_PAIS];
    int i;

    printf("           WAR ESTRUTURADO     \n\n");
    printf("---------CADASTRO DE 5 PAÍSES---------\n");

    //Faz o Cadastro para 5 Países
    for (i = 0; i < MAX_PAIS; i++) {
        printf("Digite o nome do País %d: ", i + 1 );
        fgets(paises[i].nome,MAX_NOME,stdin);
        paises[i].nome[strcspn(paises[i].nome, "\r\n")] = 0; // Remove o Enter

        printf("Digite a cor do País: ");
        fgets(paises[i].cor, MAX_COR, stdin);
        paises[i].cor[strcspn(paises[i].cor, "\r\n")] = 0; // Remove o Enter

        printf("Digite a Quantidade de Tropas nesse País: ");
        scanf("%d", &paises[i].tropas);
        printf("\n");
        limparBuffer();


    }

    printf("          WAR ESTRUTURADO     \n\n");
    printf("---------PAÍSES CADASTRADOS---------\n");
    // Laço Para mostrar os resultados
    for(i = 0; i < MAX_PAIS; i++){
        printf("--------------------------------\n");
        printf("País %d\n", i + 1);
        printf("NOME: %s\n", paises[i].nome);
        printf("COR: %s\n", paises[i].cor);
        printf("TROPAS: %d\n\n", paises[i].tropas);
    }
    printf("Aperte Enter para sair!");
    getchar();
    return 0;
}