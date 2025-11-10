#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma sala da mansão
typedef struct Sala {
    char nome[50];             // Nome da sala
    struct Sala *esquerda;     // Caminho à esquerda
    struct Sala *direita;      // Caminho à direita
} Sala;

// -----------------------------------------------------------
// Função: criarSala()
// Cria dinamicamente uma sala com o nome informado
// -----------------------------------------------------------
Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memória para a sala '%s'.\n", nome);
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// -----------------------------------------------------------
// Função: explorarSalas()
// Permite o jogador navegar entre os cômodos da mansão
// até chegar em um cômodo sem saídas.
// -----------------------------------------------------------
void explorarSalas(Sala *atual) {
    char escolha;

    printf("\nVocê está em: 🏠 %s\n", atual->nome);

    // Caso a sala não tenha saídas, o jogo termina aqui
    if (atual->esquerda == NULL && atual->direita == NULL) {
        printf("\n🔍 Você chegou ao fim da exploração! Não há mais caminhos.\n");
        return;
    }

    // Exibe opções disponíveis
    printf("Caminhos disponíveis:\n");
    if (atual->esquerda != NULL)
        printf(" - (e) Ir para %s\n", atual->esquerda->nome);
    if (atual->direita != NULL)
        printf(" - (d) Ir para %s\n", atual->direita->nome);

    // Recebe a escolha do jogador
    printf("Escolha seu caminho (e/d): ");
    scanf(" %c", &escolha);

    if (escolha == 'e' && atual->esquerda != NULL) {
        explorarSalas(atual->esquerda);
    } 
    else if (escolha == 'd' && atual->direita != NULL) {
        explorarSalas(atual->direita);
    } 
    else {
        printf("\n⚠️ Caminho inválido! Tente novamente.\n");
        explorarSalas(atual); // Tenta novamente
    }
}

// -----------------------------------------------------------
// Função principal: main()
// Monta o mapa da mansão (árvore binária)
// e inicia a exploração.
// -----------------------------------------------------------
int main() {
    // Montagem automática do mapa (árvore binária)
    Sala *hall = criarSala("Hall de Entrada");
    Sala *salaEstar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *jardim = criarSala("Jardim");
    Sala *porao = criarSala("Porão");

    // Conectando os cômodos (estrutura da mansão)
    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    cozinha->direita = porao;

    // Início da exploração
    printf("===========================================\n");
    printf("🔎 Bem-vindo(a) ao Detective Quest!\n");
    printf("Explore a mansão para descobrir o mistério.\n");
    printf("===========================================\n");

    explorarSalas(hall);

    // Liberação de memória (boa prática)
    free(hall);
    free(salaEstar);
    free(cozinha);
    free(biblioteca);
    free(jardim);
    free(porao);

    printf("\n🏁 Fim da exploração. Obrigado por jogar!\n");
    return 0;
}