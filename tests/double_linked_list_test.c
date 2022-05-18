#include <stdlib.h>
#include <time.h>

#include <check.h>

#include "nds_double_linked_list.h"

START_TEST(test_nds_dllist_node_new) {
  time_t t = time(NULL);
  nds_dllist_node_t *node = nds_dllist_node_new(&t);

  ck_assert_ptr_eq(node->data, &t);
  nds_dllist_node_free(node);

  node = nds_dllist_node_new(NULL);
  ck_assert_ptr_eq(node->data, NULL);
  nds_dllist_node_free(node);
}
END_TEST

START_TEST(test_nds_dllist_list_push) {
  nds_dllist_node_t *node0 = nds_dllist_node_new(NULL);
  nds_dllist_node_t *node1 = nds_dllist_node_new(NULL);
  nds_dllist_node_t *node2 = nds_dllist_node_new(NULL);

  nds_dllist_t list = {};

  ck_assert_uint_eq(1, nds_dllist_push(&list, node0));
  ck_assert_ptr_eq(node0, list.tail);
  ck_assert_ptr_eq(list.tail, list.head);
  ck_assert_uint_eq(1, list.length);

  ck_assert_uint_eq(2, nds_dllist_push(&list, node1));
  ck_assert_uint_eq(2, list.length);
  ck_assert_ptr_eq(node0, list.head);
  ck_assert_ptr_eq(node1, list.tail);
  ck_assert_ptr_eq(node1, list.head->next);
  ck_assert_ptr_eq(node0, list.tail->prev);

  ck_assert_uint_eq(3, nds_dllist_push(&list, node2));
  ck_assert_uint_eq(3, list.length);
  ck_assert_ptr_eq(node0, list.head);
  ck_assert_ptr_eq(node1, node0->next);
  ck_assert_ptr_eq(node2, node1->next);
  ck_assert_ptr_eq(node1, node2->prev);
  ck_assert_ptr_eq(node0, node1->prev);
  ck_assert_ptr_eq(node2, list.tail);

  nds_dllist_node_free(node0);
  nds_dllist_node_free(node1);
  nds_dllist_node_free(node2);
}
END_TEST

START_TEST(test_nds_dllist_list_pop) {
  nds_dllist_node_t *node0 = nds_dllist_node_new(NULL);
  nds_dllist_node_t *node1 = nds_dllist_node_new(NULL);
  nds_dllist_node_t *node2 = nds_dllist_node_new(NULL);

  nds_dllist_t list = {};

  ck_assert_uint_eq(1, nds_dllist_push(&list, node0));
  ck_assert_uint_eq(2, nds_dllist_push(&list, node1));
  ck_assert_uint_eq(3, nds_dllist_push(&list, node2));

  ck_assert_ptr_eq(node2, nds_dllist_pop(&list));
  ck_assert_uint_eq(2, list.length);
  ck_assert_ptr_eq(node1, list.tail);
  ck_assert_ptr_eq(NULL, node1->next);
  ck_assert_ptr_eq(NULL, node2->prev);
  ck_assert_ptr_eq(NULL, node2->next);
  ck_assert_ptr_eq(node0, list.head);

  ck_assert_ptr_eq(node1, nds_dllist_pop(&list));
  ck_assert_uint_eq(1, list.length);
  ck_assert_ptr_eq(node0, list.tail);
  ck_assert_ptr_eq(node0, list.head);

  ck_assert_ptr_eq(node0, nds_dllist_pop(&list));
  ck_assert_uint_eq(0, list.length);

  nds_dllist_node_free(node0);
  nds_dllist_node_free(node1);
  nds_dllist_node_free(node2);
}
END_TEST

START_TEST(test_nds_dllist_list_unshift) {
  nds_dllist_node_t *node0 = nds_dllist_node_new(NULL);
  nds_dllist_node_t *node1 = nds_dllist_node_new(NULL);
  nds_dllist_node_t *node2 = nds_dllist_node_new(NULL);

  nds_dllist_t list = {};

  ck_assert_uint_eq(1, nds_dllist_unshift(&list, node0));
  ck_assert_uint_eq(1, list.length);
  ck_assert_ptr_eq(node0, list.head);
  ck_assert_ptr_eq(node0, list.tail);

  ck_assert_uint_eq(2, nds_dllist_unshift(&list, node1));
  ck_assert_uint_eq(2, list.length);
  ck_assert_ptr_eq(node1, list.head);
  ck_assert_ptr_eq(node0, node1->next);
  ck_assert_ptr_eq(node1, node0->prev);
  ck_assert_ptr_eq(node0, list.tail);

  ck_assert_uint_eq(3, nds_dllist_unshift(&list, node2));
  ck_assert_uint_eq(3, list.length);
  ck_assert_ptr_eq(node2, list.head);
  ck_assert_ptr_eq(node1, node2->next);
  ck_assert_ptr_eq(node0, node1->next);
  ck_assert_ptr_eq(node1, node0->prev);
  ck_assert_ptr_eq(node2, node1->prev);
  ck_assert_ptr_eq(node0, list.tail);

  nds_dllist_node_free(node0);
  nds_dllist_node_free(node1);
  nds_dllist_node_free(node2);
}

START_TEST(test_nds_dllist_list_shift) {
  nds_dllist_node_t *node0 = nds_dllist_node_new(NULL);
  nds_dllist_node_t *node1 = nds_dllist_node_new(NULL);
  nds_dllist_node_t *node2 = nds_dllist_node_new(NULL);

  nds_dllist_t list = {};

  nds_dllist_unshift(&list, node0);
  nds_dllist_unshift(&list, node1);
  nds_dllist_unshift(&list, node2);

  ck_assert_ptr_eq(node2, nds_dllist_shift(&list));
  ck_assert_uint_eq(2, list.length);
  ck_assert_ptr_eq(node1, list.head);
  ck_assert_ptr_eq(NULL, node1->prev);
  ck_assert_ptr_eq(NULL, node2->next);
  ck_assert_ptr_eq(NULL, node2->prev);
  ck_assert_ptr_eq(node0, list.tail);

  ck_assert_ptr_eq(node1, nds_dllist_shift(&list));
  ck_assert_uint_eq(1, list.length);
  ck_assert_ptr_eq(node0, list.head);
  ck_assert_ptr_eq(node0, list.tail);

  ck_assert_ptr_eq(node0, nds_dllist_shift(&list));
  ck_assert_uint_eq(0, list.length);

  nds_dllist_node_free(node0);
  nds_dllist_node_free(node1);
  nds_dllist_node_free(node2);
}

START_TEST(test_nds_dllist_list_remove) {
  nds_dllist_node_t *node0 = nds_dllist_node_new(NULL);
  nds_dllist_node_t *node1 = nds_dllist_node_new(NULL);
  nds_dllist_node_t *node2 = nds_dllist_node_new(NULL);
  nds_dllist_node_t *node3 = nds_dllist_node_new(NULL);

  nds_dllist_t list = {};

  nds_dllist_unshift(&list, node0);
  nds_dllist_unshift(&list, node1);
  nds_dllist_unshift(&list, node2);
  nds_dllist_unshift(&list, node3);

  ck_assert_ptr_eq(node1, nds_dllist_remove(&list, node1));
  ck_assert_uint_eq(3, list.length);
  ck_assert_ptr_eq(node3, list.head);
  ck_assert_ptr_eq(node0, node2->next);
  ck_assert_ptr_eq(node2, node0->prev);
  ck_assert_ptr_eq(node0, list.tail);

  ck_assert_ptr_eq(node3, nds_dllist_remove(&list, node3));
  ck_assert_uint_eq(2, list.length);
  ck_assert_ptr_eq(node2, list.head);
  ck_assert_ptr_eq(node0, node2->next);
  ck_assert_ptr_eq(node2, node0->prev);
  ck_assert_ptr_eq(node0, list.tail);

  ck_assert_ptr_eq(node0, nds_dllist_remove(&list, node0));
  ck_assert_uint_eq(1, list.length);
  ck_assert_ptr_eq(node2, list.tail);
  ck_assert_ptr_eq(node2, list.head);
  ck_assert_ptr_eq(node2, nds_dllist_remove(&list, node2));
  ck_assert_uint_eq(0, list.length);

  nds_dllist_node_free(node0);
  nds_dllist_node_free(node1);
  nds_dllist_node_free(node2);
  nds_dllist_node_free(node3);
}

START_TEST(test_nds_dllist_list_insert_before) {
  nds_dllist_node_t *node0 = nds_dllist_node_new(NULL);
  nds_dllist_node_t *node1 = nds_dllist_node_new(NULL);
  nds_dllist_node_t *node2 = nds_dllist_node_new(NULL);
  nds_dllist_node_t *node3 = nds_dllist_node_new(NULL);

  nds_dllist_t list = {};

  // node0 -> NULL
  ck_assert_uint_eq(1, nds_dllist_insert_before(&list, node0, NULL));
  ck_assert_uint_eq(1, list.length);
  ck_assert_ptr_eq(node0, list.tail);
  ck_assert_ptr_eq(node0, list.head);

  // node1 -> node0 -> NULL
  ck_assert_uint_eq(2, nds_dllist_insert_before(&list, node1, node0));
  ck_assert_uint_eq(2, list.length);
  ck_assert_ptr_eq(node0, list.tail);
  ck_assert_ptr_eq(node1, node0->prev);
  ck_assert_ptr_eq(node0, node1->next);
  ck_assert_ptr_eq(node1, list.head);

  // node1 -> node2 -> node0 -> NULL
  ck_assert_uint_eq(3, nds_dllist_insert_before(&list, node2, node0));
  ck_assert_uint_eq(3, list.length);
  ck_assert_ptr_eq(node0, list.tail);
  ck_assert_ptr_eq(node1, node2->prev);
  ck_assert_ptr_eq(node2, node0->prev);
  ck_assert_ptr_eq(node0, node2->next);
  ck_assert_ptr_eq(node2, node1->next);
  ck_assert_ptr_eq(node1, list.head);

  // node1 -> node3 -> node2 -> node0 -> NULL
  ck_assert_uint_eq(4, nds_dllist_insert_before(&list, node3, node2));
  ck_assert_uint_eq(4, list.length);
  ck_assert_ptr_eq(node0, list.tail);
  ck_assert_ptr_eq(node1, node3->prev);
  ck_assert_ptr_eq(node3, node2->prev);
  ck_assert_ptr_eq(node2, node0->prev);
  ck_assert_ptr_eq(node0, node2->next);
  ck_assert_ptr_eq(node2, node3->next);
  ck_assert_ptr_eq(node3, node1->next);
  ck_assert_ptr_eq(node1, list.head);

  nds_dllist_node_free(node0);
  nds_dllist_node_free(node1);
  nds_dllist_node_free(node2);
  nds_dllist_node_free(node3);
}

Suite *nds_double_linked_list_suite() {
  Suite *s = suite_create("double_linked_list");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_nds_dllist_node_new);
  tcase_add_test(tc_core, test_nds_dllist_list_push);
  tcase_add_test(tc_core, test_nds_dllist_list_pop);
  tcase_add_test(tc_core, test_nds_dllist_list_unshift);
  tcase_add_test(tc_core, test_nds_dllist_list_shift);
  tcase_add_test(tc_core, test_nds_dllist_list_remove);
  tcase_add_test(tc_core, test_nds_dllist_list_insert_before);
  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  Suite *suite = nds_double_linked_list_suite();
  SRunner *sr = srunner_create(suite);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}