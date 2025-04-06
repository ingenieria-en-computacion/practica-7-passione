#include <check.h>
#include <stdlib.h>
#define LINKED_LIST_IMPLEMENTATION
#include "linkedlist.h"
#include "circular_linkedlist.h"

// Función auxiliar para imprimir enteros (usada en pruebas)
void print_int(int value) {
    printf("%d ", value);
}

/* ------------------------------------- */
/* Tests para listas de enteros (List_int) */
/* ------------------------------------- */

START_TEST(test_list_create) {
    List_int* list = list_int_create();
    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(list->head);
    ck_assert_ptr_null(list->tail);
    ck_assert_uint_eq(list->length, 0);
    list_int_destroy(list);
}
END_TEST

START_TEST(test_append_and_length) {
    List_int* list = list_int_create();
    
    ck_assert(list_int_append(list, 10));
    ck_assert_uint_eq(list_int_length(list), 1);
    
    ck_assert(list_int_append(list, 20));
    ck_assert_uint_eq(list_int_length(list), 2);
    
    list_int_destroy(list);
}
END_TEST

START_TEST(test_insert_and_get) {
    List_int* list = list_int_create();
    int value = 0;
    
    list_int_insert(list, 10, 0);
    list_int_insert(list, 30, 1);
    list_int_insert(list, 20, 1);    
    
    ck_assert(list_int_get(list, 1, &value));
    ck_assert_int_eq(value, 20);
    
    list_int_destroy(list);
}
END_TEST

START_TEST(test_remove) {
    List_int* list = list_int_create();
    list_int_append(list, 10);
    list_int_append(list, 20);
    list_int_append(list, 30);
    
    ck_assert(list_int_remove_at(list, 1));  
    ck_assert_uint_eq(list_int_length(list), 2);
    
    int value = 0;
    ck_assert(list_int_get(list, 1, &value));
    ck_assert_int_eq(value, 30);  
    
    list_int_destroy(list);
}

/* ------------------------------------- */
/* Tests para listas circulares de caracteres (CircularList_char) */
/* ------------------------------------- */

START_TEST(test_circular_list_create) {
    CircularList_char* list = circular_list_char_create();
    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(list->head);
    ck_assert_uint_eq(list->length, 0);
    circular_list_char_destroy(list);
}
END_TEST

START_TEST(test_circular_append_and_length) {
    CircularList_char* list = circular_list_char_create();
    
    ck_assert(circular_list_char_append(list, 'a'));
    ck_assert_uint_eq(circular_list_char_length(list), 1);
    
    ck_assert(circular_list_char_append(list, 'b'));
    ck_assert_uint_eq(circular_list_char_length(list), 2);
    
    circular_list_char_destroy(list);
}
END_TEST

START_TEST(test_circular_get) {
    CircularList_char* list = circular_list_char_create();
    
    circular_list_char_append(list, 'a');
    circular_list_char_append(list, 'b');
    circular_list_char_append(list, 'c');

    char value;
    ck_assert(circular_list_char_get(list, 1, (void**)&value));
    ck_assert_int_eq(value, 'b');  
    
    circular_list_char_destroy(list);
}
END_TEST

START_TEST(test_circular_remove) {
    CircularList_char* list = circular_list_char_create();
    circular_list_char_append(list, 'a');
    circular_list_char_append(list, 'b');
    circular_list_char_append(list, 'c');
    
    ck_assert(circular_list_char_remove_at(list, 1));  // Elimina 'b'
    ck_assert_uint_eq(circular_list_char_length(list), 2);
    
    char value;
    ck_assert(circular_list_char_get(list, 1, (void**)&value));
    ck_assert_int_eq(value, 'c');  // Debe devolver 'c'
    
    circular_list_char_destroy(list);
}

/* ------------------------------------- */
/* Suite de pruebas principal */
/* ------------------------------------- */

Suite* linked_list_suite(void) {
    Suite* s = suite_create("Linked List");
    
    TCase* tc_core = tcase_create("Core Functions");
    
    // Tests para lista ligada
    tcase_add_test(tc_core, test_list_create);
    tcase_add_test(tc_core, test_append_and_length);
    tcase_add_test(tc_core, test_insert_and_get);
    tcase_add_test(tc_core, test_remove);
    
    // Tests para lista circular
    tcase_add_test(tc_core, test_circular_list_create);
    tcase_add_test(tc_core, test_circular_append_and_length);
    tcase_add_test(tc_core, test_circular_get);
    tcase_add_test(tc_core, test_circular_remove);
    
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
