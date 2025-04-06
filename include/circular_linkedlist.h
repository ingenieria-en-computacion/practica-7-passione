#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// ----------------------------
// Macro para declarar estructuras y prototipos
// ----------------------------
#define DECLARE_CIRCULAR_LINKED_LIST(TYPE) \
    typedef struct CircularNode_##TYPE { \
        TYPE data; \
        struct CircularNode_##TYPE* next; \
    } CircularNode_##TYPE; \
    CircularNode_##TYPE* circular_node_##TYPE##__create(TYPE); \
    typedef struct { \
        CircularNode_##TYPE* head; \
        size_t length; \
    } CircularList_##TYPE; \
    CircularList_##TYPE* circular_list_##TYPE##_create(void); \
    void circular_list_##TYPE##_destroy(CircularList_##TYPE* list); \
    bool circular_list_##TYPE##_append(CircularList_##TYPE* list, TYPE data); \
    bool circular_list_##TYPE##_remove_at(CircularList_##TYPE* list, size_t pos); \
    size_t circular_list_##TYPE##_length(const CircularList_##TYPE* list); \
    void circular_list_##TYPE##_print(const CircularList_##TYPE* list, void (*print_fn)(TYPE));

// ----------------------------
// Macro para implementación de listas circulares
// ----------------------------
#define IMPLEMENT_CIRCULAR_LINKED_LIST(TYPE) \
    CircularNode_##TYPE* circular_node_##TYPE##__create(TYPE data) { \
        CircularNode_##TYPE* new_node = malloc(sizeof(CircularNode_##TYPE)); \
        new_node->data = data; \
        new_node->next = new_node; \
        return new_node; \
    } \
    CircularList_##TYPE* circular_list_##TYPE##_create(void) { \
        CircularList_##TYPE* list = malloc(sizeof(CircularList_##TYPE)); \
        if (!list) return NULL; \
        list->head = NULL; \
        list->length = 0; \
        return list; \
    } \
    void circular_list_##TYPE##_destroy(CircularList_##TYPE* list) { \
        if (!list) return; \
        CircularNode_##TYPE* current = list->head; \
        if (!current) { \
            free(list); \
            return; \
        } \
        CircularNode_##TYPE* temp; \
        do { \
            temp = current; \
            current = current->next; \
            free(temp); \
        } while (current != list->head); \
        free(list); \
    } \
    bool circular_list_##TYPE##_append(CircularList_##TYPE* list, TYPE data) { \
        CircularNode_##TYPE* new_node = circular_node_##TYPE##__create(data); \
        if (!new_node) return false; \
        if (!list->head) { \
            list->head = new_node; \
        } else { \
            CircularNode_##TYPE* tail = list->head; \
            while (tail->next != list->head) { \
                tail = tail->next; \
            } \
            tail->next = new_node; \
        } \
        new_node->next = list->head; \
        list->length++; \
        return true; \
    } \
    bool circular_list_##TYPE##_remove_at(CircularList_##TYPE* list, size_t pos) { \
        if (!list || pos >= list->length) return false; \
        CircularNode_##TYPE* current = list->head; \
        CircularNode_##TYPE* prev = NULL; \
        if (pos == 0) { \
            while (current->next != list->head) { \
                current = current->next; \
            } \
            CircularNode_##TYPE* to_delete = list->head; \
            list->head = list->head->next; \
            current->next = list->head; \
            free(to_delete); \
        } else { \
            for (size_t i = 0; i < pos; ++i) { \
                prev = current; \
                current = current->next; \
            } \
            prev->next = current->next; \
            free(current); \
        } \
        list->length--; \
        return true; \
    } \
    size_t circular_list_##TYPE##_length(const CircularList_##TYPE* list) { \
        return list ? list->length : 0; \
    } \
    void circular_list_##TYPE##_print(const CircularList_##TYPE* list, void (*print_fn)(TYPE)) { \
        if (!list || !print_fn) return; \
        CircularNode_##TYPE* current = list->head; \
        if (!current) return; \
        do { \
            print_fn(current->data); \
            current = current->next; \
        } while (current != list->head); \
        printf("\n"); \
    }

// ----------------------------
// Declaración para tipos concretos de listas circulares
// ----------------------------
DECLARE_CIRCULAR_LINKED_LIST(int)
DECLARE_CIRCULAR_LINKED_LIST(char)
DECLARE_CIRCULAR_LINKED_LIST(float)

// ----------------------------
// Implementación para tipos concretos de listas circulares
// ----------------------------
#ifdef LINKED_LIST_IMPLEMENTATION
IMPLEMENT_CIRCULAR_LINKED_LIST(int)
IMPLEMENT_CIRCULAR_LINKED_LIST(char)
IMPLEMENT_CIRCULAR_LINKED_LIST(float)
#endif
