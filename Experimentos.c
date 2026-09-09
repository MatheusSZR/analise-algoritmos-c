#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define REPETICOES 32

static volatile int resultado_global = 0;

static long long agora_ns(void) {
    static LARGE_INTEGER frequencia = {0};
    LARGE_INTEGER contador;

    if (frequencia.QuadPart == 0) {
        QueryPerformanceFrequency(&frequencia);
    }

    QueryPerformanceCounter(&contador);

    return (long long)((contador.QuadPart * 1000000000LL) /
                       frequencia.QuadPart);
}

/* P1 */
static int contarZerosIterativo(int *matriz, int n) {
    int contador = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matriz[i * n + j] == 0)
                contador++;
    return contador;
}

static int contarZerosRecursivoAux(int *matriz, int n, int pos,
                                   int *profundidade, int *pico) {
    if (pos == n * n)
        return 0;

    (*profundidade)++;
    if (*profundidade > *pico)
        *pico = *profundidade;

    int atual = matriz[pos] == 0 ? 1 : 0;
    int resultado = atual + contarZerosRecursivoAux(
        matriz, n, pos + 1, profundidade, pico
    );

    (*profundidade)--;
    return resultado;
}

static int contarZerosRecursivo(int *matriz, int n, int *pico) {
    int profundidade = 0;
    return contarZerosRecursivoAux(matriz, n, 0, &profundidade, pico);
}

/* P2 */
static void inverterIterativo(char texto[], int n) {
    for (int i = 0; i < n / 2; i++) {
        char temp = texto[i];
        texto[i] = texto[n - 1 - i];
        texto[n - 1 - i] = temp;
    }
}

static void inverterRecursivo(char texto[], int inicio, int fim,
                              int *profundidade, int *pico) {
    if (inicio >= fim)
        return;

    (*profundidade)++;
    if (*profundidade > *pico)
        *pico = *profundidade;

    char temp = texto[inicio];
    texto[inicio] = texto[fim];
    texto[fim] = temp;

    inverterRecursivo(texto, inicio + 1, fim - 1,
                      profundidade, pico);

    (*profundidade)--;
}

/* P3 */
static int maiorOcorrenciaIterativo(const char texto[]) {
    int frequencia[256] = {0};

    for (int i = 0; texto[i] != '\0'; i++)
        frequencia[(unsigned char)texto[i]]++;

    int maior = 0;
    for (int i = 0; i < 256; i++)
        if (frequencia[i] > maior)
            maior = frequencia[i];

    return maior;
}

static int contarCaracterRecursivo(const char texto[], char caractere,
                                   int indice, int *profundidade, int *pico) {
    if (texto[indice] == '\0')
        return 0;

    (*profundidade)++;
    if (*profundidade > *pico)
        *pico = *profundidade;

    int atual = texto[indice] == caractere ? 1 : 0;

    int resultado = atual + contarCaracterRecursivo(
        texto, caractere, indice + 1, profundidade, pico
    );

    (*profundidade)--;
    return resultado;
}

static int maiorOcorrenciaRecursivo(const char texto[], int indice,
                                    int maior, int *profundidade, int *pico) {
    if (texto[indice] == '\0')
        return maior;

    (*profundidade)++;
    if (*profundidade > *pico)
        *pico = *profundidade;

    int profundidade_contagem = 0;
    int quantidade = contarCaracterRecursivo(
        texto, texto[indice], 0, &profundidade_contagem, pico
    );

    if (quantidade > maior)
        maior = quantidade;

    int resultado = maiorOcorrenciaRecursivo(
        texto, indice + 1, maior, profundidade, pico
    );

    (*profundidade)--;
    return resultado;
}

static int *gerarMatriz(int n) {
    int *matriz = malloc((size_t)n * n * sizeof(int));
    if (!matriz) return NULL;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matriz[i * n + j] = (i + j) % 3;

    return matriz;
}

static char *gerarString(int n) {
    char *texto = malloc((size_t)n + 1);
    if (!texto) return NULL;

    for (int i = 0; i < n; i++)
        texto[i] = (char)('A' + (i % 5));

    texto[n] = '\0';
    return texto;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Uso: %s <problema> <tipo> <N> <arquivo.csv>\n", argv[0]);
        return 1;
    }

    int problema = atoi(argv[1]);
    const char *tipo = argv[2];
    int n = atoi(argv[3]);
    const char *arquivo = argv[4];

    if (problema < 1 || problema > 3 || n <= 0)
        return 1;

    if (strcmp(tipo, "iterativo") != 0 &&
        strcmp(tipo, "recursivo") != 0)
        return 1;

    int *matriz = NULL;
    char *texto_base = NULL;
    char *texto_trabalho = NULL;

    if (problema == 1) {
        matriz = gerarMatriz(n);
        if (!matriz) return 1;
    } else {
        texto_base = gerarString(n);
        texto_trabalho = malloc((size_t)n + 1);

        if (!texto_base || !texto_trabalho) {
            free(texto_base);
            free(texto_trabalho);
            return 1;
        }
    }

    long long tempo_total = 0;
    int pilha_maxima = 1;

    for (int repeticao = 0; repeticao < REPETICOES; repeticao++) {
        if (problema == 2)
            memcpy(texto_trabalho, texto_base, (size_t)n + 1);

        long long inicio = agora_ns();

        if (problema == 1) {
            if (strcmp(tipo, "iterativo") == 0) {
                resultado_global = contarZerosIterativo(matriz, n);
                pilha_maxima = 1;
            } else {
                int pico = 0;
                resultado_global = contarZerosRecursivo(matriz, n, &pico);
                if (pico > pilha_maxima)
                    pilha_maxima = pico;
            }
        } else if (problema == 2) {
            if (strcmp(tipo, "iterativo") == 0) {
                inverterIterativo(texto_trabalho, n);
                pilha_maxima = 1;
            } else {
                int profundidade = 0;
                int pico = 0;
                inverterRecursivo(texto_trabalho, 0, n - 1,
                                  &profundidade, &pico);
                if (pico > pilha_maxima)
                    pilha_maxima = pico;
            }
        } else {
            if (strcmp(tipo, "iterativo") == 0) {
                resultado_global = maiorOcorrenciaIterativo(texto_base);
                pilha_maxima = 1;
            } else {
                int profundidade = 0;
                int pico = 0;
                resultado_global = maiorOcorrenciaRecursivo(
                    texto_base, 0, 0, &profundidade, &pico
                );
                if (pico > pilha_maxima)
                    pilha_maxima = pico;
            }
        }

        long long fim = agora_ns();
        tempo_total += fim - inicio;
    }

    double tempo_medio = (double)tempo_total / REPETICOES;

    FILE *out = fopen(arquivo, "w");
    if (!out) {
        free(matriz);
        free(texto_base);
        free(texto_trabalho);
        return 1;
    }

    fprintf(out, "N,tempo_medio_ns,profundidade_pilha_maxima\n");
    fprintf(out, "%d,%.2f,%d\n", n, tempo_medio, pilha_maxima);
    fclose(out);

    printf("Experimento concluido.\n");
    printf("Problema: %d\n", problema);
    printf("Tipo: %s\n", tipo);
    printf("N: %d\n", n);
    printf("Repeticoes: %d\n", REPETICOES);
    printf("Tempo medio: %.2f ns\n", tempo_medio);
    printf("Profundidade maxima da pilha: %d\n", pilha_maxima);
    printf("Arquivo: %s\n", arquivo);

    free(matriz);
    free(texto_base);
    free(texto_trabalho);

    return 0;
}
