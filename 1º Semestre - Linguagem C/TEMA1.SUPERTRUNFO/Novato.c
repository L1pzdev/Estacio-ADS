#include <stdio.h>

// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das Cartas

int main() {
    // Declaração de Variaveis
    char codigo_cidade1[4], codigo_cidade2[4];
    char nome_cidade1[20], nome_cidade2[20];
    int populacao_cidade1, populacao_cidade2;
    float area_cidade1, area_cidade2;
    float pib_cidade1, pib_cidade2;
    int num_pontos_turisticosc1,num_pontos_turisticosc2;
    
    // CADASTRO DE CARTA 1
    printf("CADASTRO CARTA 1\n");
    
    printf("Código da Cidade 1: ");
    scanf("%s", codigo_cidade1);

    printf("Nome de Cidade 1: ");	
    scanf("%s", nome_cidade1);

    printf("População Cidade 1: ");
    scanf("%d", &populacao_cidade1);

    printf("Área da Cidade 1: ");
    scanf("%f", &area_cidade1);

    printf("PIB Cidade 1: ");
    scanf("%f", &pib_cidade1);

    printf("Numero de Pontos Turisticos Cidade 1: ");
    scanf("%d", &num_pontos_turisticosc1);

    //CADASTRO DE CARTA 2
    printf("\n\nCADASTRO CARTA 2\n");
    
    printf("Código da Cidade 2: ");
    scanf("%s", codigo_cidade2);

    printf("Nome de Cidade 2: ");	
    scanf("%s", nome_cidade2);

    printf("População Cidade 2: ");
    scanf("%d", &populacao_cidade2);

    printf("Área da Cidade 2: ");
    scanf("%f", &area_cidade2);

    printf("PIB Cidade 2: ");
    scanf("%f", &pib_cidade2);

    printf("Numero de Pontos Turisticos Cidade 2: ");
    scanf("%d", &num_pontos_turisticosc2);


    // Exiba os valores inseridos para cada atributo da cidade, um por linha.
    // Exibição dos Dados das Cartas:
    printf("\n\nCARTA CADASTRADA 1");
    printf("\nCódigo da Cidade 1: %s", codigo_cidade1);
    printf("\nNome da Cidade: %s", nome_cidade1);
    printf("\nPopulacao: %d", populacao_cidade1);
    printf("\nArea: %.2f", area_cidade1);
    printf("\nPIB: %.2f", pib_cidade1);
    printf("\nPontos Turisticos: %d", num_pontos_turisticosc1);

    printf("\n\nCARTA CADASTRADA 2");
    printf("\nCódigo da Cidade 2: %s", codigo_cidade2);
    printf("\nNome da Cidade: %s", nome_cidade2);
    printf("\nPopulacao: %d", populacao_cidade2);
    printf("\nArea: %.2f", area_cidade2);
    printf("\nPIB: %.2f", pib_cidade2);
    printf("\nPontos Turisticos: %d", num_pontos_turisticosc2);
    return 0;
}
