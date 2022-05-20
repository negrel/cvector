#include <stdlib.h>

#include <check.h>

#include "vector.h"

START_TEST(test_nds_vector_new) {
  int *vec = nds_vector_new(10, sizeof(int));

  ck_assert_int_eq(nds_vector_cap(vec), 10);
  ck_assert_int_eq(nds_vector_len(vec), 0);

  nds_vector_free(vec);
}
END_TEST

START_TEST(test_nds_vector_push) {
  const size_t initial_cap = 4;

  int *vec = nds_vector_new(initial_cap, sizeof(int));
  nds_vector_push(&vec); // Element should be zeroed
  ck_assert_int_eq(nds_vector_len(vec), 1);

  *nds_vector_push(&vec) = 1;
  ck_assert_int_eq(nds_vector_len(vec), 2);

  *nds_vector_push(&vec) = 2;
  ck_assert_int_eq(nds_vector_len(vec), 3);

  *nds_vector_push(&vec) = 3;
  ck_assert_int_eq(nds_vector_len(vec), 4);

  ck_assert_int_eq(vec[0], 0);
  ck_assert_int_eq(vec[1], 1);
  ck_assert_int_eq(vec[2], 2);
  ck_assert_int_eq(vec[3], 3);

  vec[0] = -1;
  ck_assert_int_eq(vec[0], -1);

  // let's push again so our vector grows
  *nds_vector_push(&vec) = 4;
  ck_assert_int_eq(nds_vector_len(vec), 5);

  ck_assert_int_eq(vec[0], -1);
  ck_assert_int_eq(vec[1], 1);
  ck_assert_int_eq(vec[2], 2);
  ck_assert_int_eq(vec[3], 3);
  ck_assert_int_eq(vec[4], 4);

  ck_assert_int_gt(nds_vector_cap(vec), initial_cap);
}
END_TEST

START_TEST(test_nds_vector_pop) {
  const size_t initial_cap = 4;

  int *vec = nds_vector_new(initial_cap, sizeof(int));
  nds_vector_push(&vec); // Element should be zeroed
  *nds_vector_push(&vec) = 1;
  *nds_vector_push(&vec) = 2;
  *nds_vector_push(&vec) = 3;
  ck_assert_int_eq(nds_vector_len(vec), 4);

  int popped = 0;
  nds_vector_pop(vec, &popped);
  ck_assert_int_eq(popped, 3);
  ck_assert_int_eq(nds_vector_len(vec), 3);

  // Let's skip that one, shouldn't segfault
  nds_vector_pop(vec, NULL);
  ck_assert_int_eq(nds_vector_len(vec), 2);

  nds_vector_pop(vec, &popped);
  ck_assert_int_eq(popped, 1);
  ck_assert_int_eq(nds_vector_len(vec), 1);

  nds_vector_pop(vec, &popped);
  ck_assert_int_eq(popped, 0);
  ck_assert_int_eq(nds_vector_len(vec), 0);

  // Pop with a length of zero should'nt change the variable
  popped = 99;
  nds_vector_pop(vec, &popped);
  ck_assert_int_eq(popped, 99);

  // Lendth should remain 0
  ck_assert_int_eq(nds_vector_len(vec), 0);
}
END_TEST

START_TEST(test_nds_vector_unshift) {
  const size_t initial_cap = 4;

  int *vec = nds_vector_new(initial_cap, sizeof(int));
  nds_vector_unshift(&vec); // Element should be zeroed
  ck_assert_int_eq(nds_vector_len(vec), 1);

  *nds_vector_unshift(&vec) = 1;
  ck_assert_int_eq(nds_vector_len(vec), 2);

  *nds_vector_unshift(&vec) = 2;
  ck_assert_int_eq(nds_vector_len(vec), 3);

  *nds_vector_unshift(&vec) = 3;
  ck_assert_int_eq(nds_vector_len(vec), 4);

  ck_assert_int_eq(vec[0], 3);
  ck_assert_int_eq(vec[1], 2);
  ck_assert_int_eq(vec[2], 1);
  ck_assert_int_eq(vec[3], 0);

  vec[0] = -1;
  ck_assert_int_eq(vec[0], -1);

  // let's push again so our vector grows
  *nds_vector_unshift(&vec) = 4;
  ck_assert_int_eq(nds_vector_len(vec), 5);

  ck_assert_int_eq(vec[0], 4);
  ck_assert_int_eq(vec[1], -1);
  ck_assert_int_eq(vec[2], 2);
  ck_assert_int_eq(vec[3], 1);
  ck_assert_int_eq(vec[4], 0);

  ck_assert_int_gt(nds_vector_cap(vec), initial_cap);
}
END_TEST

START_TEST(test_nds_vector_shift) {
  const size_t initial_cap = 4;

  int *vec = nds_vector_new(initial_cap, sizeof(int));
  nds_vector_push(&vec); // Element should be zeroed
  *nds_vector_push(&vec) = 1;
  *nds_vector_push(&vec) = 2;
  *nds_vector_push(&vec) = 3;
  ck_assert_int_eq(nds_vector_len(vec), 4);

  int shifted = 0;
  nds_vector_shift(vec, &shifted);
  ck_assert_int_eq(shifted, 0);
  ck_assert_int_eq(nds_vector_len(vec), 3);

  // Let's skip that one, shouldn't segfault
  nds_vector_shift(vec, NULL);
  ck_assert_int_eq(nds_vector_len(vec), 2);

  nds_vector_shift(vec, &shifted);
  ck_assert_int_eq(shifted, 2);
  ck_assert_int_eq(nds_vector_len(vec), 1);

  nds_vector_shift(vec, &shifted);
  ck_assert_int_eq(shifted, 3);
  ck_assert_int_eq(nds_vector_len(vec), 0);

  // Pop with a length of zero should'nt change the variable
  shifted = 99;
  nds_vector_shift(vec, &shifted);
  ck_assert_int_eq(shifted, 99);

  // Lendth should remain 0
  ck_assert_int_eq(nds_vector_len(vec), 0);
}
END_TEST

START_TEST(test_nds_vector_clone) {
  int *vec = nds_vector_new(10, sizeof(int));
  *nds_vector_push(&vec) = 5;
  *nds_vector_push(&vec) = 6;

  int *clone = nds_vector_clone(vec);
  ck_assert_int_eq(clone[0], 5);
  ck_assert_int_eq(clone[1], 6);

  nds_vector_pop(clone, NULL);
  ck_assert_int_eq(nds_vector_len(clone), 1);

  ck_assert_int_eq(nds_vector_len(vec), 2);
  ck_assert_int_eq(vec[1], 6);

  nds_vector_free(clone);
  nds_vector_free(vec);
}
END_TEST

START_TEST(test_nds_vector_foreach) {
  int *vec = nds_vector_new(10, sizeof(int));
  *nds_vector_push(&vec) = 5;
  *nds_vector_push(&vec) = 6;
  *nds_vector_push(&vec) = 8;

  size_t i = 0;
  nds_vector_foreach(vec, it) {
    switch (it.index) {
      case 0:
        ck_assert_int_eq(5, it.value);
        break;

      case 1:
        ck_assert_int_eq(6, it.value);
        break;

      default:
        continue;
    }
    i++;
  }

  ck_assert_uint_eq(2, i);

  nds_vector_free(vec);
}
END_TEST

Suite *nds_vector_suite() {
  Suite *s = suite_create("vector");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_nds_vector_new);
  tcase_add_test(tc_core, test_nds_vector_push);
  tcase_add_test(tc_core, test_nds_vector_pop);
  tcase_add_test(tc_core, test_nds_vector_unshift);
  tcase_add_test(tc_core, test_nds_vector_shift);
  tcase_add_test(tc_core, test_nds_vector_clone);
  tcase_add_test(tc_core, test_nds_vector_foreach);
  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  Suite *suite = nds_vector_suite();
  SRunner *sr = srunner_create(suite);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}