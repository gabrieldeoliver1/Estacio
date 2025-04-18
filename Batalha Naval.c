#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Tamanho das matrizes de habilidade (usar matriz ímpar para facilitar centralização)
#define TAM_HABILIDADE 5

// Função para exibir o tabuleiro no console
// 0 = água, 3 = navio, 5 = área afetada pela habilidade
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("Tabuleiro com Navios e Areas de Efeito:\n\n");
    for (int linha = 0; linha < TAM_TABULEIRO; linha++) {
        for (int coluna = 0; coluna < TAM_TABULEIRO; coluna++) {
            int val = tabuleiro[linha][coluna];
            if (val == 0) {
                printf("~ ");  // Água
            } else if (val == 3) {
                printf("N ");  // Navio
            } else if (val == 5) {
                printf("* ");  // Área afetada
            } else {
                printf("? ");  // Valor inesperado
            }
        }
        printf("\n");
    }
}

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para posicionar navio no tabuleiro (horizontal ou vertical)
void posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                     int linhaInicio, int colunaInicio,
                     int tamanho, char orientacao) {
    if (orientacao == 'H') {
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linhaInicio][colunaInicio + i] = 3;
        }
    } else if (orientacao == 'V') {
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linhaInicio + i][colunaInicio] = 3;
        }
    }
}

// Função para posicionar navio diagonal crescente (linha e coluna aumentam)
void posicionarNavioDiagonal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                             int linhaInicio, int colunaInicio,
                             int tamanho, char tipoDiagonal) {
    // tipoDiagonal: 'D' para diagonal crescente, 'I' para diagonal invertida
    if (tipoDiagonal == 'D') {
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linhaInicio + i][colunaInicio + i] = 3;
        }
    } else if (tipoDiagonal == 'I') {
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linhaInicio + i][colunaInicio - i] = 3;
        }
    }
}

// Função para criar matriz de habilidade "Cone" (5x5)
// Cone apontando para baixo, topo no centro da primeira linha
void criarMatrizCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    // Inicializa tudo com 0
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            matriz[i][j] = 0;
        }
    }
    // Construir cone: linha 0 centro; linha 1 +-1; linha 2 +-2; etc.
    int centro = TAM_HABILIDADE / 2;
    for (int linha = 0; linha < TAM_HABILIDADE; linha++) {
        int inicio = centro - linha;
        int fim = centro + linha;
        if (inicio < 0) inicio = 0;
        if (fim >= TAM_HABILIDADE) fim = TAM_HABILIDADE - 1;
        for (int col = inicio; col <= fim; col++) {
            matriz[linha][col] = 1;
        }
    }
}

// Função para criar matriz de habilidade "Cruz" (5x5)
// Cruz com ponto de origem no centro
void criarMatrizCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == centro || j == centro) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade "Octaedro" (5x5)
// Losango com ponto de origem no centro
void criarMatrizOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int distLinha = (i > centro) ? i - centro : centro - i;
            int distCol = (j > centro) ? j - centro : centro - j;
            // Condição para formar losango: soma das distâncias <= centro
            matriz[i][j] = (distLinha + distCol <= centro) ? 1 : 0;
        }
    }
}

// Função para sobrepor matriz de habilidade ao tabuleiro
// Marca as posições afetadas com valor 5
void sobreporHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                        int habilidade[TAM_HABILIDADE][TAM_HABILIDADE],
                        int origemLinha, int origemColuna) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Calcula posição no tabuleiro
            int tabLinha = origemLinha - centro + i;
            int tabColuna = origemColuna - centro + j;

            // Verifica limites do tabuleiro
            if (tabLinha >= 0 && tabLinha < TAM_TABULEIRO &&
                tabColuna >= 0 && tabColuna < TAM_TABULEIRO) {
                // Se a posição da habilidade é 1 e não é navio, marca com 5
                if (habilidade[i][j] == 1 && tabuleiro[tabLinha][tabColuna] != 3) {
                    tabuleiro[tabLinha][tabColuna] = 5;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Posicionar dois navios horizontais/verticais
    posicionarNavio(tabuleiro, 2, 3, TAM_NAVIO, 'H'); // Linha 2, coluna 3, horizontal
    posicionarNavio(tabuleiro, 5, 7, TAM_NAVIO, 'V'); // Linha 5, coluna 7, vertical

    // Posicionar dois navios diagonais
    posicionarNavioDiagonal(tabuleiro, 1, 1, TAM_NAVIO, 'D'); // Diagonal crescente
    posicionarNavioDiagonal(tabuleiro, 3, 9, TAM_NAVIO, 'I'); // Diagonal invertida

    // Criar matrizes das habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    criarMatrizCone(cone);
    criarMatrizCruz(cruz);
    criarMatrizOctaedro(octaedro);

    // Definir pontos de origem das habilidades no tabuleiro
    int origemConeLinha = 0, origemConeColuna = 4;     // Topo central
    int origemCruzLinha = 5, origemCruzColuna = 5;     // Centro do tabuleiro
    int origemOctaedroLinha = 8, origemOctaedroColuna = 2; // Próximo ao canto inferior esquerdo

    // Sobrepor as áreas de efeito no tabuleiro
    sobreporHabilidade(tabuleiro, cone, origemConeLinha, origemConeColuna);
    sobreporHabilidade(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    sobreporHabilidade(tabuleiro, octaedro, origemOctaedroLinha, origemOctaedroColuna);

    // Exibir o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
