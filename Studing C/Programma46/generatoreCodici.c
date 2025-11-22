#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TOTAL_CODICI 10000
#define VINCE 100
#define CODICE_LENGTH 6

void generaCodice(char *codice, int length) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < length; i++) {
        int r = rand() % (sizeof(charset) - 1);
        codice[i] = charset[r];
    }
    codice[length] = '\0';
}

void shuffle(char **codici, int *vincitori, int total) {
    for (int i = total - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        // scambio codici
        char *tempCodice = codici[i];
        codici[i] = codici[j];
        codici[j] = tempCodice;

        // scambio vincitori
        int tempV = vincitori[i];
        vincitori[i] = vincitori[j];
        vincitori[j] = tempV;
    }
}

int main(void) {
    srand((unsigned int)time(NULL));

    // Allocazione dinamica
    char **codici = malloc(TOTAL_CODICI * sizeof(char *));
    int *vincitori = malloc(TOTAL_CODICI * sizeof(int));

    for (int i = 0; i < TOTAL_CODICI; i++) {
        codici[i] = malloc((CODICE_LENGTH + 1) * sizeof(char));
        generaCodice(codici[i], CODICE_LENGTH);
        vincitori[i] = (i < VINCE) ? 1 : 0;
    }

    shuffle(codici, vincitori, TOTAL_CODICI);

    FILE *fp = fopen("codici.json", "w");
    if (!fp) {
        fprintf(stderr, "Errore nell'apertura del file!\n");
        return 1;
    }

    fprintf(fp, "{\n");
    for (int i = 0; i < TOTAL_CODICI; i++) {
        fprintf(fp, "  \"%s\": %s", codici[i], vincitori[i] ? "true" : "false");
        if (i < TOTAL_CODICI - 1) fprintf(fp, ",\n");
        else fprintf(fp, "\n");
    }
    fprintf(fp, "}\n");
    fclose(fp);

    printf("File codici.json creato con successo!\n");

    // Libera memoria
    for (int i = 0; i < TOTAL_CODICI; i++) free(codici[i]);
    free(codici);
    free(vincitori);

    return 0;
}
