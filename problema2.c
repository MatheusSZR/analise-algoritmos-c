#include <stdio.h>
#include <string.h>

void inverterIterativo(char texto[]) {
    int inicio = 0;
    int fim = (int)strlen(texto) - 1;

    while (inicio < fim) {
        char temp = texto[inicio];
        texto[inicio] = texto[fim];
        texto[fim] = temp;
        inicio++;
        fim--;
    }
}

void inverterRecursivo(char texto[], int inicio, int fim) {
    if (inicio >= fim) {
        return;
    }

    char temp = texto[inicio];
    texto[inicio] = texto[fim];
    texto[fim] = temp;

    inverterRecursivo(texto, inicio + 1, fim - 1);
}

int main(void) {
    char iterativo[] = "BANANA";
    char recursivo[] = "BANANA";

    inverterIterativo(iterativo);
    inverterRecursivo(recursivo, 0, (int)strlen(recursivo) - 1);

    printf("Iterativo: %s\n", iterativo);
    printf("Recursivo: %s\n", recursivo);

    return 0;
}
