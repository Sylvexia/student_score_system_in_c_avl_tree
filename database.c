#include "database.h"
//ref: https://www.programiz.com/dsa/avl-tree

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
        printf("overwrite at id: %s\n", student->student_id);
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

StudentNode *delete_student_node(StudentNode *node, char *student_id)
{
    if (node == NULL)
    {
        return node;
    }

    if (strcmp(student_id, node->student->student_id) < 0)
    {
        node->left = delete_student_node(node->left, student_id);
    }
    else if (strcmp(student_id, node->student->student_id) > 0)
    {
        node->right = delete_student_node(node->right, student_id);
    }
    else
    {
        if (node->left == NULL || node->right == NULL)
        {
            StudentNode *temp = node->left ? node->left : node->right;
            if (temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else
            {
                *node = *temp;
            }
            free(temp);
        }
        else
        {
            StudentNode *temp = get_min_node(node->right);
            node->student = temp->student;
            node->right = delete_student_node(node->right, temp->student->student_id);
        }
    }

    if (node == NULL)
    {
        return node;
    }

    node->height = 1 + max(get_height(node->left), get_height(node->right));

    int balance = get_balance(node);
    if (balance > 1 && get_balance(node->left) >= 0)
    {
        return right_rotate(node);
    }
    if (balance < -1 && get_balance(node->right) <= 0)
    {
        return left_rotate(node);
    }
    if (balance > 1 && get_balance(node->left) < 0)
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    if (balance < -1 && get_balance(node->right) > 0)
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

StudentNode *search_student_node(StudentNode *node, char *student_id)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (strcmp(student_id, node->student->student_id) < 0)
    {
        return search_student_node(node->left, student_id);
    }
    else if (strcmp(student_id, node->student->student_id) > 0)
    {
        return search_student_node(node->right, student_id);
    }
    else
    {
        return node;
    }
}

void print_student_ranks(StudentNode *node, Student *student)
{
    int total_rank, english_rank, math_rank, science_rank = 1;

    get_student_ranks(node, student, &total_rank, &english_rank, &math_rank, &science_rank);

    printf("total rank: %d, english_rank: %d, math_rank: %d, science_rank: %d\n", total_rank, english_rank, math_rank, science_rank);
}

void get_student_ranks(StudentNode *node, Student *student, int *total_rank, int *english_rank, int *math_rank, int *science_rank)
{
    if (node == NULL)
    {
        return;
    }

    double student_total_score = student->score.english + student->score.math + student->score.science;
    double node_total_score = node->student->score.english + node->student->score.math + node->student->score.science;

    if(student->score.english > node->student->score.english)
    {
        *english_rank += 1;
    }
    if(student->score.math > node->student->score.math)
    {
        *math_rank += 1;
    }
    if(student->score.science > node->student->score.science)
    {
        *science_rank += 1;
    }
    if(student_total_score > node_total_score)
    {
        *total_rank += 1;
    }

    get_student_ranks(node->left, student, total_rank, english_rank, math_rank, science_rank);
    get_student_ranks(node->right, student, total_rank, english_rank, math_rank, science_rank);

}

void destroy_student_node(StudentNode *node)
{
    if (node == NULL)
    {
        return;
    }
    destroy_student_node(node->left);
    destroy_student_node(node->right);
    free(node);
}

void print_student_node_inorder(StudentNode *node)
{
    if (node == NULL)
    {
        return;
    }
    print_student_node_inorder(node->left);
    print_student(node->student);
    printf("\n");
    print_student_node_inorder(node->right);
}

StudentNode *load_student_node_from_csv(StudentNode *node, char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("file not found\n");
        return NULL;
    }

    char line[LINE_SIZE_MAX];
    while (fgets(line, sizeof(line), fp))
    {
        char *token = strtok(line, ",");
        char *student_id = token;
        token = strtok(NULL, ",");
        int english = atoi(token);
        token = strtok(NULL, ",");
        int math = atoi(token);
        token = strtok(NULL, ",");
        int science = atoi(token);
        Student *student = create_student(student_id, english, math, science);
        node = insert_student_node(node, student);
    }
    return node;
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

StudentNode *get_min_node(StudentNode *node)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->left == NULL)
    {
        return node;
    }
    return get_min_node(node->left);
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

int get_size(StudentNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return get_size(node->left) + get_size(node->right) + 1;
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

void print_student(Student *student)
{
    printf("id: %s\n", student->student_id);
    printf("english: %lf\n", student->score.english);
    printf("math: %lf\n", student->score.math);
    printf("science: %lf\n", student->score.science);
}

void print_student_evaluate(StudentNode *node, Student *student)
{   
    print_student(student);
    printf("total: %lf\n", student->score.english + student->score.math + student->score.science);
    printf("average: %lf\n", (student->score.english + student->score.math + student->score.science) / 3.0);
    print_student_ranks(node, student);
}