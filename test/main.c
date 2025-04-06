#include <check.h>
#include <stdlib.h>
#define LINKED_LIST_IMPLEMENTATION
#include "linkedlist.h"

// Función auxiliar para imprimir enteros (usada en pruebas)
void print_int(int value) {
    printf("%d ", value);
}

// Función auxiliar para liberar memoria de enteros
void destroy_int(void* data) {
    free(data);
}

// Función auxiliar para comparar enteros
bool int_cmp(int a, int b) {
    return a == b;
}

/* ------------------------------------- */
/* Tests para listas de enteros (List_int) */
/* ------------------------------------- */

START_TEST(test_list_create) {
    List* list = list_create(destroy_int);
    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(list->head);
    ck_assert_uint_eq(list->length, 0);
    list_destroy(list);
}
END_TEST

START_TEST(test_append_and_length) {
    List* list = list_create(destroy_int);
    
    int* num1 = malloc(sizeof(int));
    *num1 = 10;
    ck_assert(list_append(list, num1));
    ck_assert_uint_eq(list_length(list), 1);
    
    int* num2 = malloc(sizeof(int));
    *num2 = 20;
    ck_assert(list_append(list, num2));
    ck_assert_uint_eq(list_length(list), 2);
    
    list_destroy(list);
}
END_TEST

START_TEST(test_insert_and_get) {
    List* list = list_create(destroy_int);
    int value = 0;

    int* num1 = malloc(sizeof(int));
    *num1 = 10;
    list_insert(list, num1, 0);
    
    int* num2 = malloc(sizeof(int));
    *num2 = 30;
    list_insert(list, num2, 1);
    
    int* num3 = malloc(sizeof(int));
    *num3 = 20;
    list_insert(list, num3, 1);    
    
    ck_assert(list_get(list, 1, (void**)&value));
    ck_assert_int_eq(value, 20);
    
    list_destroy(list);
}
END_TEST

START_TEST(test_remove) {
    List* list = list_create(destroy_int);
    
    int* num1 = malloc(sizeof(int));
    *num1 = 10;
    list_append(list, num1);
    
    int* num2 = malloc(sizeof(int));
    *num2 = 20;
    list_append(list, num2);
    
    int* num3 = malloc(sizeof(int));
    *num3 = 30;
    list_append(list, num3);
    
    ck_assert(list_remove_at(list, 1));  // Elimina 20
    ck_assert_uint_eq(list_length(list), 2);
    
    int value = 0;
    ck_assert(list_get(list, 1, (void**)&value));
    ck_assert_int_eq(value, 30);  // Lista: [10, 30]
    
    list_destroy(list);
}
END_TEST

/* ------------------------------------- */
/* Suite de pruebas principal */
/* ------------------------------------- */

Suite* linked_list_suite(void) {
    Suite* s = suite_create("Linked List");
    
    TCase* tc_core = tcase_create("Core Functions");
    tcase_add_test(tc_core, test_list_create);
    tcase_add_test(tc_core, test_append_and_length);
    tcase_add_test(tc_core, test_insert_and_get);
    tcase_add_test(tc_core, test_remove);
    
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    SRunner* sr = srunner_create(linked_list_suite());
    
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
