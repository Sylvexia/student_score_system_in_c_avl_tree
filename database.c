#include "database.h"
//ref: https://www.programiz.com/dsa/avl-tree

int test_database(int type_size)
{
    printf("num received: %d\n", type_size);
    return type_size;
}

StudentNode *create_student_node(Student *new_student)
{
    StudentNode *new_node = (StudentNode *)malloc(sizeof(StudentNode));
    new_node->student = new_student;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    return new_node;
}

StudentNode *insert_student_node(StudentNode *node, Student *student)
{
    if (node == NULL)
    {
        node = create_student_node(student);
        return node;
    }

    if (strcmp(student->student_id, node->student->student_id) < 0)
    {
        node->left = insert_student_node(node->left, student);
    }
    else if (strcmp(student->student_id, node->student->student_id) > 0)
    {
        node->right = insert_student_node(node->right, student);
    }
    else
    {
        //overwrite
        node->student = create_student(student->student_id, student->score.english, student->score.math, student->score.science);
    }

    node->height = 1 + max(get_height(node->left), get_height(node->right));

    int balance = get_balance(node);
    if (balance > 1 && strcmp(student->student_id, node->left->student->student_id) < 0)
    {
        return right_rotate(node);
    }
    if (balance < -1 && strcmp(student->student_id, node->right->student->student_id) > 0)
    {
        return left_rotate(node);
    }
    if (balance > 1 && strcmp(student->student_id, node->left->student->student_id) > 0)
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    if (balance < -1 && strcmp(student->student_id, node->right->student->student_id) < 0)
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

void print_student_node(StudentNode *node)
{
    if (node == NULL)
    {
        return;
    }
    print_student_node(node->left);
    printf("%s\n", node->student->student_id);
    print_student_node(node->right);
}

StudentNode *right_rotate(StudentNode *root)
{
    StudentNode *left_child = root->left;
    StudentNode *left_right_child = left_child->right;

    left_child->right = root;
    root->left = left_right_child;

    root->height = 1 + max(get_height(root->left), get_height(root->right));
    left_child->height = 1 + max(get_height(left_child->left), get_height(left_child->right));

    return left_child;
}

StudentNode *left_rotate(StudentNode *root)
{
    StudentNode *right_child = root->right;
    StudentNode *right_left_child = right_child->left;

    right_child->left = root;
    root->right = right_left_child;

    root->height = 1 + max(get_height(root->left), get_height(root->right));
    right_child->height = 1 + max(get_height(right_child->left), get_height(right_child->right));

    return right_child;
}

int get_height(StudentNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

int get_balance(StudentNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return get_height(node->left) - get_height(node->right);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

Student *create_student(char *student_id, double english, double math, double science)
{
    Student *new_student = (Student *)malloc(sizeof(Student));
    strcpy(new_student->student_id, student_id);
    new_student->score.english = english;
    new_student->score.math = math;
    new_student->score.science = science;
    return new_student;
}