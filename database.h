#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_ID_LENGTH 10
#define LINE_SIZE_MAX 255
typedef enum subject
{
    ENGLISH = 1,
    MATH = 2,
    SCIENCE = 3,
} Subject;

typedef struct scores
{
    double english;
    double math;
    double science;
} Scores;

// struct for student
typedef struct student
{
    char student_id[STUDENT_ID_LENGTH + 1];
    Scores score;
} Student;

// student avl tree
typedef struct student_node
{
    Student *student;
    struct student_node *left;
    struct student_node *right;
    int height;
} StudentNode;

StudentNode *create_student_node(Student *student);
StudentNode *insert_student_node(StudentNode *node, Student *student);
StudentNode *insert_student_node_with_overwrite_log(StudentNode *node, Student *student);
StudentNode *delete_student_node(StudentNode *node, char *student_id);
StudentNode *search_student_node(StudentNode *node, char *student_id);
void print_student_ranks(StudentNode *node, Student *student);
void get_student_ranks(StudentNode *node, Student *student, int *total_rank, int *english_rank, int *math_rank, int *science_rank);
void destroy_student_node(StudentNode *node);
void print_student_node_inorder(StudentNode *node);
StudentNode *load_student_node_from_csv(StudentNode *node, char *file_name);
void save_student_node_to_csv(StudentNode *node, char *file_name);
void save_student_node_to_csv_recursive(StudentNode *node, FILE *fp);

StudentNode *right_rotate(StudentNode *root);
StudentNode *left_rotate(StudentNode *root);
StudentNode *get_min_node(StudentNode *root);
int get_height(StudentNode *root);
int get_balance(StudentNode *root);
int get_size(StudentNode *root);
void get_math_score_array(StudentNode *node, double *math_array, int *index);
void get_english_score_array(StudentNode *node, double *english_array, int *index);
void get_science_score_array(StudentNode *node, double *science_array, int *index);
void get_total_score_array(StudentNode *node, double *total_array, int *index);
void create_score_array(double *array, int *index, int size);
void destroy_score_array(double *array);
int max(int a, int b);
void swap(double *a, double *b);

Student *create_student(char *student_id, double english, double math, double science);
void print_student(Student *student);
void print_student_evaluate(StudentNode *node, Student *student);

typedef struct student_score
{
    char student_id[STUDENT_ID_LENGTH + 1];
    double score;
} StudentScore;

typedef struct score_min_heap
{
    int size;
    int index;
    StudentScore *student_scores; // array of student scores
} ScoreMinHeap;

ScoreMinHeap *create_score_min_heap(ScoreMinHeap *heap, int k);
ScoreMinHeap *insert_score_min_heap(ScoreMinHeap *heap, StudentScore *student_score);
ScoreMinHeap *swap_score_min_heap_index(ScoreMinHeap *heap, int i, int j);
void destroy_score_min_heap(ScoreMinHeap *heap);
void heapify_score_min_heap(ScoreMinHeap *heap, int i);
void get_english_score_min_heap(ScoreMinHeap *heap, StudentNode *node);
void get_math_score_min_heap(ScoreMinHeap *heap, StudentNode *node);
void get_science_score_min_heap(ScoreMinHeap *heap, StudentNode *node);
void get_total_score_min_heap(ScoreMinHeap *heap, StudentNode *node);
void print_score_min_heap(ScoreMinHeap *heap);