#include <stdio.h>

#define TAM_TAB 10
#define TAM_HAB 5

#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    for (int i = 0; i < TAM_TAB; i++)
        for (int j = 0; j < TAM_TAB; j++)
            tabuleiro[i][j] = AGUA;
}

// Função para construir a matriz da habilidade em cone (base inferior)
void construirHabilidadeCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= TAM_HAB / 2 - i && j <= TAM_HAB / 2 + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para construir a matriz da habilidade em cruz
void construirHabilidadeCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para construir a matriz da habilidade em octaedro (losango)
void construirHabilidadeOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para aplicar uma matriz de habilidade no tabuleiro
void aplicarHabilidadeNoTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB],
                                  int habilidade[TAM_HAB][TAM_HAB],
                                  int origemLinha, int origemColuna) {
    int offset = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int linhaTab = origemLinha - offset + i;
            int colunaTab = origemColuna - offset + j;

            // Verifica se está dentro dos limites
            if (linhaTab >= 0 && linhaTab < TAM_TAB && colunaTab >= 0 && colunaTab < TAM_TAB) {
                if (habilidade[i][j] == 1 && tabuleiro[linhaTab][colunaTab] == AGUA)
                    tabuleiro[linhaTab][colunaTab] = HABILIDADE;
            }
        }
    }
}

// Posiciona navios fixos para demonstração
void posicionarNaviosFixos(int tabuleiro[TAM_TAB][TAM_TAB]) {
    // Navio horizontal em (1,2)
    for (int i = 0; i < 3; i++) tabuleiro[1][2 + i] = NAVIO;

    // Navio vertical em (4,0)
    for (int i = 0; i < 3; i++) tabuleiro[4 + i][0] = NAVIO;

    // Diagonal ↘ a partir de (0,0)
    for (int i = 0; i < 3; i++) tabuleiro[0 + i][0 + i] = NAVIO;

    // Anti-diagonal ↙ a partir de (6,9)
    for (int i = 0; i < 3; i++) tabuleiro[6 + i][9 - i] = NAVIO;
}

int main() {
    int tabuleiro[TAM_TAB][TAM_TAB];
    inicializarTabuleiro(tabuleiro);
    posicionarNaviosFixos(tabuleiro);

    // Matrizes de habilidade
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    construirHabilidadeCone(cone);
    construirHabilidadeCruz(cruz);
    construirHabilidadeOctaedro(octaedro);

    // Aplicar as habilidades no tabuleiro
    aplicarHabilidadeNoTabuleiro(tabuleiro, cone, 2, 4);      // Cone no topo
    aplicarHabilidadeNoTabuleiro(tabuleiro, cruz, 5, 5);      // Cruz no centro
    aplicarHabilidadeNoTabuleiro(tabuleiro, octaedro, 8, 2);  // Octaedro embaixo

    // Imprimir o tabuleiro final
    printf("Tabuleiro com Habilidades:\n");
    imprimirTabuleiro(tabuleiro);

    return 0;
}