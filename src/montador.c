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

// FUNÇÕES CONSTRUTORAS DA TABELA
// Retorna endereço inteiro de um dado símbolo
int get_address(char *symbol, SymTable *head){
    SymTable *aux = head;
    int addr;
    while(aux != NULL)
    {
        if(strcmp(symbol,aux->symbol) == 0)
        {
            addr = aux->mem_addr;
            break;
        }
        aux = aux->next;
    }
    return addr;
}

// Retorna 1 se tem o símbolo e 0 caso contrário
int has_symbol(char symbol[], SymTable *head){
    SymTable *aux = head;
    while (aux != NULL){
        if(strcmp(symbol,aux->symbol) == 0) return 1;
        aux = aux->next;
    }
    return 0;
}

// Adiciona símbolo se ele não estiver na tabela
SymTable * add_symbol(char symbol[], SymTable *head){
    if(has_symbol(symbol, head) == 0){
        SymTable *aux = head;
        SymTable *new;
        while (aux != NULL && aux->next != NULL) {
            aux = aux->next;
        }
        new = (SymTable *) malloc(sizeof(SymTable));
        strcpy(new->symbol, symbol);
        new->mem_addr = -1;
        new->next= NULL;
        if (aux != NULL)
            aux->next = new;
        else
            head = new;
    }
    return head;
}

// Adiciona endereço a um símbolo na tabela
// Se não acha, cria novo símbolo
SymTable * add_address(char symbol[], int addr, SymTable *head){
    SymTable *aux = head;
    SymTable *new;
    if(has_symbol(symbol, head) == 1){
        while(aux != NULL){
            if(strcmp(symbol,aux->symbol) == 0){
                aux->mem_addr = addr;
            }
            aux = aux->next;
        }
    }
    else {
        new = (SymTable *) malloc(sizeof(SymTable));
        while (aux != NULL && aux->next != NULL) {
            aux = aux->next;
        }
        strcpy(new->symbol, symbol);
        new->mem_addr = addr;
        new->next= NULL;
        if (aux != NULL)
            aux->next = new;
        else
            head = new;
    }
    return head;
}

void print_table(SymTable *head){
    SymTable *aux = head;
    printf("Símbolo \t Endereço\n");
    while (aux != NULL){
        printf("%s \t %d\n", aux->symbol, aux->mem_addr);
        aux = aux->next;
    }
}

// FUNÇÕES DO MONTADOR
// Passo 1 - Constrói tabela.
SymTable * pass_one(FILE *arq, SymTable *head){
    char line[100];
    char *word;
    int mem_addr = 1, size;
    /* 
    Lê linha por linha e a separa em tokens com "strtok()"
    Caso encontre um label ou uma palavra não declarada pela MV,
    adiciona à tabela de símbolos.
    */
    while(fgets(line, 100, arq) != NULL){
        word = strtok(line, " ");
        if (word != NULL && strncmp(word, ";", 1) != 0 && strncmp(word, "\n", 1) != 0){
            // Se termina com ":", label encontrado.
            size = strlen(word);
            if (strncmp(&word[size-1], ":", 1) == 0){
                word[size-1] = '\0';
                head = add_address(word, mem_addr, head);
                word = strtok(NULL, " ");
            }
            int i = retorna_instrucao(word);
            //Se leu instrução JUMP, JZ, JN ou CALL
            if (i == 16 || i == 17 || i == 18 || i == 19){
                word = strtok(NULL, " ");
                size = strlen(word);
                if(strncmp(&word[size-1], "\n", 1) == 0) word[size-1] = '\0';
                head = add_symbol(word, head);
            }
            // Se leu instrução LOAD ou STORE
            else if (i == 1 || i == 2){
                word = strtok(NULL, " ");
                word = strtok(NULL, " ");
                size = strlen(word);
                if(strncmp(&word[size-1], "\n", 1) == 0) word[size-1] = '\0';
                head = add_symbol(word, head);
            }
            mem_addr++;
        }
    }

    return head;
}