#include <stdio.h>
#include <string.h>

int maiorOcorrenciaIterativo(const char texto[]) {
    int frequencia[256] = {0};

    for (int i = 0; texto[i] != '\0'; i++) {
        unsigned char c = (unsigned char)texto[i];
        frequencia[c]++;
    }

    int maior = 0;
    for (int i = 0; i < 256; i++) {
        if (frequencia[i] > maior) {
            maior = frequencia[i];
        }
    }

    return maior;
}

int contarCaracter(const char texto[], char caractere, int indice) {
    if (texto[indice] == '\0') {
        return 0;
    }

    int atual = (texto[indice] == caractere) ? 1 : 0;

    return atual + contarCaracter(texto, caractere, indice + 1);
}

int maiorOcorrenciaRecursivo(const char texto[], int indice, int maior) {
    if (texto[indice] == '\0') {
        return maior;
    }

    char caractere = texto[indice];
    int quantidade = contarCaracter(texto, caractere, 0);

    if (quantidade > maior) {
        maior = quantidade;
    }

    return maiorOcorrenciaRecursivo(texto, indice + 1, maior);
}

int main(void) {
    const char texto[] = "BANANA";

    printf("Iterativo: %d\n", maiorOcorrenciaIterativo(texto));
    printf("Recursivo: %d\n", maiorOcorrenciaRecursivo(texto, 0, 0));

    return 0;
}
