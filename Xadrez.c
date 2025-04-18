#include <stdio.h>

// Constantes para o número de casas a serem movidas
#define TORRE_CASAS 5
#define BISPO_CASAS 5
#define RAINHA_CASAS 8
#define CAVALO_CIMA 2
#define CAVALO_DIREITA 1

// Função recursiva para o movimento da Torre
void torre(int casas) {
    if (casas > 0) {
        printf("Direita\n");
        torre(casas - 1);
    }
}

// Função recursiva para o movimento do Bispo
void bispo(int casas) {
    if (casas > 0) {
        printf("Cima, Direita\n");
        bispo(casas - 1);
    }
}

// Função recursiva para o movimento da Rainha
void rainha(int casas) {
    if (casas > 0) {
        printf("Esquerda\n");
        rainha(casas - 1);
    }
}

int main() {
    // Movimento da Torre: 5 casas para a direita usando recursividade
    printf("Movimento da Torre:\n");
    torre(TORRE_CASAS);

    // Movimento do Bispo: 5 casas na diagonal (Cima, Direita) usando recursividade
    printf("\n\nMovimento do Bispo:\n");
    bispo(BISPO_CASAS);

    // Movimento da Rainha: 8 casas para a esquerda usando recursividade
    printf("\n\nMovimento da Rainha:\n");
    rainha(RAINHA_CASAS);

    // Movimento do Cavalo: 2 casas para cima e 1 casa para a direita usando loops aninhados
    printf("\n\nMovimento do Cavalo:\n");
    for (int i = 0; i < CAVALO_CIMA; i++) {
        printf("Cima\n");
    }
    printf("Direita\n");

    // Movimento do Bispo com loops aninhados (para simular diagonal)
    printf("\n\nMovimento do Bispo com Loops Aninhados:\n");
    for (int i = 0; i < BISPO_CASAS; i++) {
        for (int j = 0; j < 1; j++) { // Loop interno para simular movimento horizontal
            printf("Cima, Direita\n");
        }
    }

    return 0;
}
