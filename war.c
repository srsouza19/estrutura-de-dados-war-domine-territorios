// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

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

// Implementação das funções
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
        strncpy(mapa[i].cor, cores[i], TAM_MAX_COR - 1);
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
        printf("%-15s %-15s %-10d\n", 
               mapa[i].nome, 
               mapa[i].cor, 
               mapa[i].numTropas);
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
    }
}

void faseDeAtaque(Territorio* mapa) {
    int atacante, defensor;
    
    exibirMapa(mapa);
    
    printf("\nEscolha o território atacante (1-%d): ", NUM_TERRITORIOS);
    scanf("%d", &atacante);
    limparBufferEntrada();
    
    printf("Escolha o território defensor (1-%d): ", NUM_TERRITORIOS);
    scanf("%d", &defensor);
    limparBufferEntrada();
    
    // Ajusta índices para base 0
    atacante--;
    defensor--;
    
    if (atacante >= 0 && atacante < NUM_TERRITORIOS &&
        defensor >= 0 && defensor < NUM_TERRITORIOS) {
        simularAtaque(mapa, atacante, defensor);
    } else {
        printf("Territórios inválidos!\n");
    }
}

int simularAtaque(Territorio* mapa, int atacante, int defensor) {
    // Validações
    if (mapa[atacante].numTropas <= 1) {
        printf("Território atacante precisa ter mais de 1 tropa!\n");
        return 0;
    }
    
    if (strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {
        printf("Não pode atacar território da mesma cor!\n");
        return 0;
    }
    
    // Simula dados de ataque (3) e defesa (2)
    int dadosAtaque[NUM_DADOS_ATAQUE];
    int dadosDefesa[NUM_DADOS_DEFESA];
    
    // Rola dados de ataque
    for (int i = 0; i < NUM_DADOS_ATAQUE; i++) {
        dadosAtaque[i] = (rand() % 6) + 1;
    }
    
    // Rola dados de defesa
    for (int i = 0; i < NUM_DADOS_DEFESA; i++) {
        dadosDefesa[i] = (rand() % 6) + 1;
    }
    
    // Ordena dados em ordem decrescente
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
    
    // Compara resultados
    int numComparacoes = (mapa[atacante].numTropas - 1 < mapa[defensor].numTropas) 
                        ? mapa[atacante].numTropas - 1 
                        : mapa[defensor].numTropas;
    
    if (numComparacoes > NUM_DADOS_DEFESA) numComparacoes = NUM_DADOS_DEFESA;
    
    for (int i = 0; i < numComparacoes; i++) {
        if (dadosAtaque[i] > dadosDefesa[i]) {
            mapa[defensor].numTropas--;
            printf("Defensor perdeu 1 tropa!\n");
        } else {
            mapa[atacante].numTropas--;
            printf("Atacante perdeu 1 tropa!\n");
        }
    }
    
    // Verifica conquista
    if (mapa[defensor].numTropas == 0) {
        printf("%s conquistou %s!\n", mapa[atacante].nome, mapa[defensor].nome);
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
                if (strcmp(mapa[i].cor, "Verde") == 0) {
                    return 0; // Ainda existe território Verde
                }
            }
            return 1; // Não existe mais território Verde
            
        case 1: // Conquistar 3 territórios
            int territoriosConquistados = 0;
            for (int i = 0; i < NUM_TERRITORIOS; i++) {
                if (strcmp(mapa[i].cor, corJogador) == 0) {
                    territoriosConquistados++;
                }
            }
            return (territoriosConquistados >= 3);
    }
    return 0;
}

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand((unsigned)time(NULL));
    
    Territorio* mapa = alocarMapa();
    inicializarTerritorios(mapa);
    
    char corJogador[TAM_MAX_COR];
    strcpy(corJogador, "Azul"); // Define a cor do jogador
    
    int idMissao = sortearMissao();
    int opcao;
    int vitoria = 0;
    
    do {
        exibirMapa(mapa);
        exibirMissao(idMissao);
        exibirMenuPrincipal();
        
        scanf("%d", &opcao);
        limparBufferEntrada();
        
        switch (opcao) {
            case 1:
                faseDeAtaque(mapa);
                break;
                
            case 2:
                vitoria = verificarVitoria(mapa, idMissao, corJogador);
                if (vitoria) {
                    printf("\nPARABÉNS! Você completou sua missão!\n");
                } else {
                    printf("\nMissão ainda não completada. Continue jogando!\n");
                }
                break;
                
            case 0:
                printf("Obrigado por jogar!\n");
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
