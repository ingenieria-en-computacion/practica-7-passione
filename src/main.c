#define LINKED_LIST_IMPLEMENTATION
#include "linkedlist.h"
#include "circular_linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

// Funciones para imprimir enteros
void print_int(int value) {
    printf("%d ", value);
}

int main() {
    // Crear y usar una lista ligada de enteros
    List_int* nums = list_int_create();
    int* num1 = malloc(sizeof(int));
    *num1 = 10;
    list_int_append(nums, num1);
    
    int* num2 = malloc(sizeof(int));
    *num2 = 20;
    list_int_append(nums, num2);
    
    printf("Lista de enteros: ");
    void* data;
    for (size_t i = 0; i < list_int_length(nums); i++) {
        if (list_int_get(nums, i, &data)) {
            print_int(*(int*)data);
        }
    }
    printf("\n");
    
    list_int_destroy(nums);

    // Crear y usar una lista ligada circular de caracteres
    CircularList_char* chars = circular_list_char_create();
    char* char1 = malloc(sizeof(char));
    *char1 = 'a';
    circular_list_char_append(chars, char1);
    
    char* char2 = malloc(sizeof(char));
    *char2 = 'b';
    circular_list_char_append(chars, char2);
    
    char* char3 = malloc(sizeof(char));
    *char3 = 'c';
    circular_list_char_append(chars, char3);

    printf("Lista de caracteres: ");
    for (size_t i = 0; i < circular_list_char_length(chars); i++) {
        if (circular_list_char_get(chars, i, (void**)&data)) {
            printf("%c ", *(char*)data);
        }
    }
    printf("\n");

    circular_list_char_destroy(chars);
    return 0;
}
