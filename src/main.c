#define LINKED_LIST_IMPLEMENTATION
#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

// Funciones para imprimir y comparar enteros
void print_int(int value) {
    printf("%d ", value);
}

bool int_cmp(int a, int b) {
    return a == b;
}

// Funciones para imprimir y comparar caracteres
void print_char(char value) {
    printf("%c ", value);
}

bool char_cmp(char a, char b) {
    return a == b;
}

int main() {
    // Crear y usar una lista ligada de enteros
    List* nums = list_create(free); 
    int* num1 = malloc(sizeof(int));
    *num1 = 10;
    list_append(nums, num1);
    
    int* num2 = malloc(sizeof(int));
    *num2 = 20;
    list_append(nums, num2);
    
    printf("Lista de enteros: ");
    void* data;
    for (size_t i = 0; i < list_length(nums); i++) {
        if (list_get(nums, i, &data)) {
            print_int(*(int*)data);
        }
    }
    printf("\n");
    
    list_destroy(nums);

    // Crear y usar una lista ligada de caracteres
    CircularList* chars = circular_list_create(free);
    char* char1 = malloc(sizeof(char));
    *char1 = 'a';
    circular_list_append(chars, char1);
    
    char* char2 = malloc(sizeof(char));
    *char2 = 'b';
    circular_list_append(chars, char2);
    
    char* char3 = malloc(sizeof(char));
    *char3 = 'c';
    circular_list_append(chars, char3);

    printf("Lista de caracteres: ");
    for (size_t i = 0; i < circular_list_length(chars); i++) {
        if (circular_list_get(chars, i, (void**)&data)) {
            print_char(*(char*)data);
        }
    }
    printf("\n");

    circular_list_destroy(chars);
    return 0;
}
