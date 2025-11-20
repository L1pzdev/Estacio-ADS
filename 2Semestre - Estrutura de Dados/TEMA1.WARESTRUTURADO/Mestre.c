#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constantes Globais
#define MAX_PAISES 42 //Tamanho Oficial do Jogo
#define MAX_NOME 50
#define MAX_COR 15
#define MAX_STRING 100
#define QTD_JOGADORES 5

// Definição Estrutura Territorio
struct Territorio
{
    char nome [MAX_NOME];
    char cor [MAX_COR];
    int tropas;
};

// Definição Estrutura Jogadores
struct Jogador {
    char cor [MAX_COR];
    char *missao;
};

//Definição das Missões
const char *missoesPossiveis[] = {
    "Conquistar 3 Territorios",
    "Eliminar Exército Verde",
    "Ter 15 Tropas ou mais",
    "Eliminar Exercito Vermelho",
    "Ter mais territórios que a cor Azul"
};

int qtdMissoes = 5;

// Limpa o Buffer
void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Liberar a Memória Utilizada
void liberarMemoria(struct Territorio *paises, struct Jogador *jogadores){
    if (paises != NULL){
        free(paises);
    }
    //Laço para liberar de todos os jogadores
    for (int i = 0; i < QTD_JOGADORES; i++){
        if (jogadores[i].missao != NULL){
            free(jogadores[i].missao);
        }       
    }
    printf("\nMemória Liberada com Sucesso");
}

//Atribui a missão para cada jogador Dinamicamente
void atribuirMissao(struct Jogador *jogador){
    printf("\n---- Sorteando Missões! ----\n");

    for (int i = 0; i < QTD_JOGADORES; i++){
        if (jogador[i].missao != NULL){
            free(jogador[i].missao); //Limpa a memória de jogos passados.
        }
        int sorteio = rand() % qtdMissoes;
        jogador[i].missao = (char *) malloc(MAX_STRING * sizeof(char));

        //Prevenção de Erros
        if (!jogador[i].missao){
            printf("Erro de memória na Missão!\n");
            exit(1);
        }
        strcpy(jogador[i].missao, missoesPossiveis[sorteio]);
        printf("Jogador %s recebeu uma missao secreta.\n", jogador[i].cor);
    }
}

int verificarMissao(struct Jogador *jogadores, struct Territorio *paises, int totalPaises){
    int contagemTerritorios[QTD_JOGADORES] = {0};
    int contagemTropas[QTD_JOGADORES] = {0};
    //Contagem de quantos territórios e tropas cada cor possui.
    for (int i = 0; i < totalPaises; i++){
        for (int j = 0; j < QTD_JOGADORES; j++){
            if (strcmp(paises[i].cor, jogadores[j].cor) == 0){
                contagemTropas[j] += paises[i].tropas;
                contagemTerritorios[j]++;
                break; //Ao encontrar o índice correspondente ele passa pro próximo país cadastrado
            }
        }
    }

    //Passar por cada condição da missão e descobrir quem venceu!
    for (int i = 0; i < QTD_JOGADORES; i++){
        char *missao = jogadores[i].missao;
        int terminarJogo = 0; //Se Alguem cumpriu a missao finaliza o jogo[0 - Jogo Continua; 1 - Temos um Vencedor]

        if (strcmp(missao, "Conquistar 3 Territorios") == 0){ //Missão 1: Conquistar 3 Territórios
            if (contagemTerritorios[i] >= 3) terminarJogo = 1;
        } 
        else if (strcmp(missao, "Eliminar Exército Verde") == 0){ //Missao 2: Eliminar Jogador Verde
            if (contagemTerritorios[3] == 0 && i != 3) terminarJogo = 1;
        }
        else if (strcmp(missao, "Eliminar Exército Vermelho") == 0){ //Missao 3: Eliminar Jogador Vermelho
            if(contagemTerritorios[1] == 0 && i != 1) terminarJogo = 1;
        }
        else if (strcmp(missao, "Ter 15 Tropas ou mais") == 0){ //Missao 4: Ter 15 Tropas ou mais
            if (contagemTropas[i] >= 15) terminarJogo =1;
        }
        else if (strcmp(missao, "Ter mais territórios que a cor Azul") == 0){
            if(contagemTerritorios[i] > contagemTerritorios[0] && i != 0) terminarJogo = 1;
        }

        if (terminarJogo == 1){
            printf("\n\n=================================\n");
            printf("JOGO TERMINOU! TEMOS UM VENCEDOR!\n");
            printf("=================================\n");
            printf("Vencedor: Jogador %s\n", jogadores[i].cor);
            printf("Missão Completa: %s\n", jogadores[i].missao);
            return 1;
        }
    }
    return 0;
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
        atacante->tropas += 2;
        strcpy(defensor->cor, atacante->cor);
        int tropasMovidas = atacante->tropas /2;
        if (tropasMovidas < 1) tropasMovidas = 1;
        defensor->tropas = tropasMovidas;
        atacante->tropas = atacante->tropas - tropasMovidas;

        printf("O territorio agora pertence a cor %s!\n", atacante->cor);
    } else {
        printf("Defesa segurou! O Atacante perdeu tropas. \n");
        if (atacante->tropas > 0){
            atacante->tropas --;
            defensor->tropas ++; //Ganha a Tropa do Atacante, Prisioneiro de Guerra
        }
    }
}

void exibirMapa(struct Territorio *paises, int totalPaises){
    printf("--- MAPA MUNDI ---\n\n");
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
}
//Função que controla o Menu com o Jogo Iniciado
int iniciarJogo(int totalPaises, struct Territorio *paises, struct Jogador *jogadores){
    int escolha;
    do
    {
        printf("=================================\n");
        printf("          JOGO INICIADO          \n");
        printf("=================================\n");
        printf("1 - Atacar País\n");
        printf("2 - Mostrar todos os territórios\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        limparBuffer();

        switch (escolha)
        {
        case 1:
        //Atribuição Aleatória de Ataque e Defesa
            int atacante = rand() % totalPaises;
            int defensor;
            int tentativas = 0; //Controlador de Tentativas
            do
            {
                defensor = rand() % totalPaises;
                tentativas++;
            } while ((atacante == defensor || strcmp(paises[atacante].cor, paises[defensor].cor) == 0) && tentativas < 100); //Limite de 100 Tentativas para evitar fogo amigo
            if (tentativas >= 100)
            {
                printf("Nenhum inimigo valido encontrado");
            } else {
                atacar(&paises[atacante], &paises[defensor]);
                int resultado = verificarMissao(jogadores,paises,totalPaises); //Chamamos a funcao para verificar se temos vencedor
                if (resultado == 1){
                    printf("Pressione Enter para encerrar...");
                    getchar();
                    return 1;
                }
            }
            printf("Pressione Enter para encerrar...");
            getchar();
            break;
        
        case 2:
            exibirMapa(paises, totalPaises);
            printf("\nPressione Enter para continuar...");
            getchar();
            break;
        
        case 0:
            printf("Voltando ao Menu Principal...\n");
            break;

        default:
            printf("Opção Inválida!\n");
        }
    } while (escolha != 0); 
    return 0;
}

//Função Principal
int main(){
    //Inicializa a Biblioteca Rand
    srand(time(NULL));

    //Definição de Ponteiros e Alocação de Memória
    struct Territorio *paises;
    paises = (struct Territorio *) calloc(MAX_PAISES, sizeof(struct Territorio));

    //Definimos Estrutura de Jogadores e Suas Respectivas cores
    struct Jogador jogadores[QTD_JOGADORES];
    strcpy(jogadores[0].cor, "Azul");
    strcpy(jogadores[1].cor, "Vermelho");
    strcpy(jogadores[2].cor, "Branco");
    strcpy(jogadores[3].cor, "Verde");
    strcpy(jogadores[4].cor, "Amarelo");

    for(int i = 0; i<QTD_JOGADORES; i++){
        jogadores[i].missao = NULL;
    }
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
        printf("3 - Mostrar todas as missões disponíveis\n");
        printf("9 - Iniciar o Jogo\n");
        printf("0 - Sair\n");
        printf("---------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoMenu);
        limparBuffer();

        switch (opcaoMenu)
        {
        case 1: //Cadastro de País
            printf("--- Cadastro de Novo País ---\n\n");
            printf("Cores Disponíveis: Azul, Vermelho, Branco, Verde, Amarelo\n");
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
            opcaoMenu = -1; //Adicionado para forçar o opcao Mudar, pois se digito 1 e depois digito um texto, ele não entrava no default.
            break;

        case 2: //Lista dos Países Cadastrados
            exibirMapa(paises,totalPaises);
            printf("\nPressione Enter para continuar...");
            getchar();
            opcaoMenu = -1;
            break;
        
        case 3: //Mostrar Missões de Cada Jogador
            printf("--- Missões Disponíveis ---\n\n"); 
            for (int i =0; i < qtdMissoes; i++){
                printf("%d. %s\n", i+1, missoesPossiveis[i]);
            }
            printf("\nPressione Enter para continuar...");
            getchar();
            opcaoMenu = -1;
            break;
        
        case 9: //Inicia o Jogo   
            if (totalPaises < 2) {
                printf("Erro: Precisa no mínimo de 2 países cadastrados!\n");
            } else {
                //Chama a função atribuindo uma missão para cada jogador
                atribuirMissao(jogadores);
                if (iniciarJogo(totalPaises, paises,jogadores) == 1){
                    opcaoMenu = 0;
                }
            }
            break;

        case 0: //Sair
            printf("Fechando o jogo...\n");
            liberarMemoria(paises,jogadores); //Chamar a Função
            break;

        default: //Sistema para Escolha Erradas
            printf("\nOpção Inválida! Escolha uma das opções acima: \n");
            break;
        }
    } while (opcaoMenu != 0); //Sai do Programa

    return 0;
    liberarMemoria(paises,jogadores);
}