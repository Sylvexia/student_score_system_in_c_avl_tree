#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char student_id[11];
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
void destroy_student_node(StudentNode *node);
void print_student_node(StudentNode *node);
void print_student_node_preorder(StudentNode *node);

StudentNode *right_rotate(StudentNode *root);
StudentNode *left_rotate(StudentNode *root);
int get_height(StudentNode *root);
int get_balance(StudentNode *root);
int max(int a, int b);

Student *create_student(char *student_id, double english, double math, double science);