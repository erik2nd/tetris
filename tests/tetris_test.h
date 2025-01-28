#ifndef TETRIS_TEST_H
#define TETRIS_TEST_H

#include <check.h>

#include "../brick_game/tetris/backend.h"

void run_test_cases(Suite *testcase);

Suite *suite_actions();
Suite *suite_instance();
Suite *suite_checkups();
Suite *suite_placing();
Suite *suite_moving();
Suite *suite_updating();
Suite *suite_clearing();
Suite *suite_values();
Suite *suite_recording();
Suite *suite_specifics();

#endif
