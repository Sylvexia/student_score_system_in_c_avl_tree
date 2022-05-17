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
    SCIENCE = 3
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
    char student_id[STUDENT_ID_LENGTH+1];
    Scores score;
} Student;

//student avl tree
typedef struct student_node
{
    Student *student;
    struct student_node *left;
    struct student_node *right;
    int height;
} StudentNode;

StudentNode *create_student_node(Student *student);
StudentNode *insert_student_node(StudentNode *node, Student *student);
StudentNode *delete_student_node(StudentNode *node, char *student_id);
StudentNode *search_student_node(StudentNode *node, char *student_id);
void print_student_ranks(StudentNode *node, Student *student);
void get_student_ranks(StudentNode *node, Student *student, int *total_rank, int *english_rank, int *math_rank, int *science_rank);
void destroy_student_node(StudentNode *node);
void print_student_node_inorder(StudentNode *node);
StudentNode *load_student_node_from_csv(StudentNode *node, char *file_name);
void save_student_node_to_csv(StudentNode *node, char *file_name);

StudentNode *right_rotate(StudentNode *root);
StudentNode *left_rotate(StudentNode *root);
StudentNode *get_min_node(StudentNode *root);
int get_height(StudentNode *root);
int get_balance(StudentNode *root);
int get_size(StudentNode *root);
int max(int a, int b);

Student *create_student(char *student_id, double english, double math, double science);
void print_student(Student *student);
void print_student_evaluate(StudentNode *node, Student *student);
