#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "database.h"

#define FILE_NAME_LENGTH 255

enum FEATURES
{
    INSERT_SINGLE_STUDENT = 1,
    LOAD_CSV = 2,
    LOG_SORTED_BY_ID = 3,
    SEARCH_BY_ID_EVALUATE = 4,
    SEARCH_TOP_TEN_SPECIFIC_SUBJECT = 5,
    SEARCH_TOP_TEN_TOTAL_SCORE = 6,
    ADD_DELETE_STUDENT = 7,
    EXIT = 8,

    INSERT_RAND_DATA = 9,
    SAVE_CSV = 10
};
void print_manual();

void user_interface();
void user_insert_studuent_id(char *student_id);
void user_insert_student_score(double *english, double *math, double *science);
void user_insert_file_name(char *file_name);

StudentNode *feature_insert_student_data(StudentNode *student_node);
StudentNode *feature_load_from_csv(StudentNode *student_node);
void feature_log_student_data_by_id(StudentNode *student_node);
void feature_search_by_id_evaluate(StudentNode *student_node);
void feature_search_top_ten_score_by_subject(StudentNode *student_node);
void feature_search_top_ten_score_by_total_score(StudentNode *student_node);
StudentNode *feature_add_delete_student_data(StudentNode *student_node);

StudentNode *feature_add_rand_data(StudentNode *student_node);
void feature_save_csv(StudentNode *student_node);