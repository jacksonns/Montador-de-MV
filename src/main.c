#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "montador.h"

int main(int argc, char *argv[]) {
    
    //Teste de leitura do arquivo
    FILE *arq;
    switch (argc) {
    case 1:
        printf("Forneça um arquivo!\n");
        return 1;
    case 2:
        arq = fopen(argv[1], "rt");
        if (arq == NULL) {
            printf("Arquivo não encontrado\n");
            return 1;
        }
    }
    

    //Imprime conteúdo ignorando comentários iniciados com ';'
    char *buf;
    while(!feof(arq)){
        if (fgets(buf, 100, arq)) {
            char *delimiter = strstr(buf, ";");
            if (delimiter) {
                *delimiter = '\0';
            }
            printf("%s\n",buf);
        }
    }

    fclose(arq);
    return 0;
}
