#include <stdio.h>

int contarZerosIterativo(int matriz[][3], int linhas, int colunas) {
    int contador = 0;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == 0) {
                contador++;
            }
        }
    }
    return contador;
}

int contarZerosRecursivo(int matriz[][3], int linha, int coluna,
                         int linhas, int colunas) {
    if (linha == linhas) {
        return 0;
    }

    int atual = (matriz[linha][coluna] == 0) ? 1 : 0;

    if (coluna + 1 < colunas) {
        return atual + contarZerosRecursivo(
            matriz, linha, coluna + 1, linhas, colunas
        );
    }

    return atual + contarZerosRecursivo(
        matriz, linha + 1, 0, linhas, colunas
    );
}

int main(void) {
    int matriz[3][3] = {
        {1, 0, 3},
        {0, 5, 0},
        {7, 8, 9}
    };

    printf("Iterativo: %d\n", contarZerosIterativo(matriz, 3, 3));
    printf("Recursivo: %d\n", contarZerosRecursivo(matriz, 0, 0, 3, 3));

    return 0;
}
