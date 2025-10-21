#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define NUM_TERRITORIOS 5
#define NUM_MISSOES 2
#define TAM_MAX_NOME 50
#define TAM_MAX_COR 20
#define NUM_DADOS_ATAQUE 3
#define NUM_DADOS_DEFESA 2

// Estrutura para representar um território
typedef struct {
    char nome[TAM_MAX_NOME];
    char cor[TAM_MAX_COR];
    int numTropas;
} Territorio;

// Protótipos das funções
Territorio* alocarMapa(void);
void inicializarTerritorios(Territorio* mapa);
void liberarMemoria(Territorio* mapa);
void exibirMenuPrincipal(void);
void exibirMapa(const Territorio* mapa);
void exibirMissao(int idMissao);
void faseDeAtaque(Territorio* mapa);
int simularAtaque(Territorio* mapa, int atacante, int defensor);
int sortearMissao(void);
int verificarVitoria(const Territorio* mapa, int idMissao, const char* corJogador);
void limparBufferEntrada(void);

// ===================================================
// Implementação das funções
// ===================================================

Territorio* alocarMapa(void) {
    Territorio* mapa = (Territorio*)calloc(NUM_TERRITORIOS, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro: Falha na alocação de memória!\n");
        exit(1);
    }
    return mapa;
}

void inicializarTerritorios(Territorio* mapa) {
    const char* nomes[] = {"Brasil", "Argentina", "Peru", "Venezuela", "Chile"};
    const char* cores[] = {"Verde", "Azul", "Vermelho", "Amarelo", "Preto"};

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        strncpy(mapa[i].nome, nomes[i], TAM_MAX_NOME - 1);
        mapa[i].nome[TAM_MAX_NOME - 1] = '\0';

        strncpy(mapa[i].cor, cores[i], TAM_MAX_COR - 1);
        mapa[i].cor[TAM_MAX_COR - 1] = '\0';

        mapa[i].numTropas = 3; // Cada território começa com 3 tropas
    }
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

void exibirMenuPrincipal(void) {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1. Atacar\n");
    printf("2. Verificar Missão\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

void exibirMapa(const Territorio* mapa) {
    printf("\n=== MAPA ATUAL ===\n");
    printf("%-15s %-15s %-10s\n", "Território", "Cor", "Tropas");
    printf("----------------------------------------\n");

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("%-15s %-15s %-10d\n", mapa[i].nome, mapa[i].cor, mapa[i].numTropas);
    }
    printf("\n");
}

void exibirMissao(int idMissao) {
    printf("\n=== SUA MISSÃO ===\n");
    switch (idMissao) {
        case 0:
            printf("Destruir o exército Verde\n");
            break;
        case 1:
            printf("Conquistar 3 territórios\n");
            break;
        default:
            printf("Missão desconhecida\n");
    }
}

void faseDeAtaque(Territorio* mapa) {
    int atacante, defensor;

    exibirMapa(mapa);

    printf("\nEscolha o território atacante (1-%d): ", NUM_TERRITORIOS);
    if (scanf("%d", &atacante) != 1) {
        limparBufferEntrada();
        printf("Entrada inválida!\n");
        return;
    }

    printf("Escolha o território defensor (1-%d): ", NUM_TERRITORIOS);
    if (scanf("%d", &defensor) != 1) {
        limparBufferEntrada();
        printf("Entrada inválida!\n");
        return;
    }

    limparBufferEntrada();

    atacante--;
    defensor--;

    if (atacante < 0 || atacante >= NUM_TERRITORIOS ||
        defensor < 0 || defensor >= NUM_TERRITORIOS) {
        printf("Territórios inválidos!\n");
        return;
    }

    if (atacante == defensor) {
        printf("O mesmo território não pode atacar a si mesmo!\n");
        return;
    }

    simularAtaque(mapa, atacante, defensor);
}

int simularAtaque(Territorio* mapa, int atacante, int defensor) {
    if (mapa[atacante].numTropas <= 1) {
        printf("Território atacante precisa ter mais de 1 tropa!\n");
        return 0;
    }

    if (strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {
        printf("Não pode atacar território da mesma cor!\n");
        return 0;
    }

    int dadosAtaque[NUM_DADOS_ATAQUE];
    int dadosDefesa[NUM_DADOS_DEFESA];

    // Rola os dados
    for (int i = 0; i < NUM_DADOS_ATAQUE; i++)
        dadosAtaque[i] = (rand() % 6) + 1;
    for (int i = 0; i < NUM_DADOS_DEFESA; i++)
        dadosDefesa[i] = (rand() % 6) + 1;

    // Ordena os dados (maior para menor)
    for (int i = 0; i < NUM_DADOS_ATAQUE - 1; i++) {
        for (int j = i + 1; j < NUM_DADOS_ATAQUE; j++) {
            if (dadosAtaque[i] < dadosAtaque[j]) {
                int temp = dadosAtaque[i];
                dadosAtaque[i] = dadosAtaque[j];
                dadosAtaque[j] = temp;
            }
        }
    }
    for (int i = 0; i < NUM_DADOS_DEFESA - 1; i++) {
        for (int j = i + 1; j < NUM_DADOS_DEFESA; j++) {
            if (dadosDefesa[i] < dadosDefesa[j]) {
                int temp = dadosDefesa[i];
                dadosDefesa[i] = dadosDefesa[j];
                dadosDefesa[j] = temp;
            }
        }
    }

    int comparacoes = (mapa[atacante].numTropas - 1 < mapa[defensor].numTropas)
                        ? mapa[atacante].numTropas - 1
                        : mapa[defensor].numTropas;
    if (comparacoes > NUM_DADOS_DEFESA) comparacoes = NUM_DADOS_DEFESA;
    if (comparacoes <= 0) comparacoes = 1;

    for (int i = 0; i < comparacoes; i++) {
        printf("\nAtaque: %d x Defesa: %d\n", dadosAtaque[i], dadosDefesa[i]);
        if (dadosAtaque[i] > dadosDefesa[i]) {
            mapa[defensor].numTropas--;
            printf("Defensor perdeu 1 tropa!\n");
        } else {
            mapa[atacante].numTropas--;
            printf("Atacante perdeu 1 tropa!\n");
        }
    }

    // Se o defensor perdeu tudo
    if (mapa[defensor].numTropas <= 0) {
        printf("\n%s conquistou %s!\n", mapa[atacante].nome, mapa[defensor].nome);
        strcpy(mapa[defensor].cor, mapa[atacante].cor);
        mapa[defensor].numTropas = 1;
        mapa[atacante].numTropas--;
        return 1;
    }

    return 0;
}

int sortearMissao(void) {
    return rand() % NUM_MISSOES;
}

int verificarVitoria(const Territorio* mapa, int idMissao, const char* corJogador) {
    switch (idMissao) {
        case 0: // Destruir exército Verde
            for (int i = 0; i < NUM_TERRITORIOS; i++) {
                if (strcmp(mapa[i].cor, "Verde") == 0)
                    return 0;
            }
            return 1;

        case 1: { // Conquistar 3 territórios
            int conquistados = 0;
            for (int i = 0; i < NUM_TERRITORIOS; i++) {
                if (strcmp(mapa[i].cor, corJogador) == 0)
                    conquistados++;
            }
            return (conquistados >= 3);
        }

        default:
            return 0;
    }
}

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    srand((unsigned)time(NULL));

    Territorio* mapa = alocarMapa();
    inicializarTerritorios(mapa);

    char corJogador[TAM_MAX_COR];
    strcpy(corJogador, "Azul");

    int idMissao = sortearMissao();
    int opcao;
    int vitoria = 0;

    do {
        exibirMapa(mapa);
        exibirMissao(idMissao);
        exibirMenuPrincipal();

        if (scanf("%d", &opcao) != 1) {
            limparBufferEntrada();
            printf("Entrada inválida!\n");
            continue;
        }

        limparBufferEntrada();

        switch (opcao) {
            case 1:
                faseDeAtaque(mapa);
                break;
            case 2:
                vitoria = verificarVitoria(mapa, idMissao, corJogador);
                if (vitoria)
                    printf("\n🎉 PARABÉNS! Você completou sua missão!\n");
                else
                    printf("\nMissão ainda não completada. Continue jogando!\n");
                break;
            case 0:
                printf("\nObrigado por jogar!\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

        if (vitoria) {
            printf("\nJogo encerrado! Você venceu!\n");
            break;
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}
