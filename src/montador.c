#include "montador.h"
#include <string.h>

// TODO: implementação do montador
int retorna_instrucao(char str[]) { //Retorna o códido das instruções
    if (strcmp(str, "HALT") == 0){
        return 0;
    } else if (strcmp(str, "LOAD") == 0) {
        return 1;
    } else if (strcmp(str, "STORE") == 0) {
        return 2;
    } else if (strcmp(str, "READ") == 0) {
        return 3;
    } else if (strcmp(str, "WRITE") == 0) {
        return 4;
    } else if (strcmp(str, "COPY") == 0) {
        return 5;
    } else if (strcmp(str, "PUSH") == 0) {
        return 6;
    } else if (strcmp(str, "POP") == 0) {
        return 7;
    } else if (strcmp(str, "ADD") == 0) {
        return 8;
    } else if (strcmp(str, "SUB") == 0) {
        return 9;
    } else if (strcmp(str, "MUL") == 0) {
        return 10;
    } else if (strcmp(str, "DIV") == 0) {
        return 11;
    } else if (strcmp(str, "MOD") == 0) {
        return 12;
    } else if (strcmp(str, "AND") == 0) {
        return 13;
    } else if (strcmp(str, "OR") == 0) {
        return 14;
    } else if (strcmp(str, "NOT") == 0) {
        return 15;
    } else if (strcmp(str, "JUMP") == 0) {
        return 16;
    } else if (strcmp(str, "JZ") == 0) {
        return 17;
    } else if (strcmp(str, "JN") == 0) {
        return 18;
    } else if (strcmp(str, "CALL") == 0) {
        return 19;
    } else if (strcmp(str, "RET") == 0) {
        return 20;
    } else if (strcmp(str, "WORD") == 0) {
        return 21;
    } else if (strcmp(str, "END") == 0) {
        return 22;
    } else {
        return -1;
    }
}

int retorna_registrador(char str[]) { //Retorna o código dos registradores de propósito geral
    return str[1] - '0';
}
