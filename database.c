#include "database.h"
#include <limits.h>
// ref: https://www.programiz.com/dsa/avl-tree

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


StudentNode *insert_student_node_with_overwrite_log(StudentNode *node, Student *student)
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
        printf("Student ID %s already exists.\n", student->student_id);
        printf("The score was: %.3f, %.3f, %.3f\n", node->student->score.english, node->student->score.english, node->student->score.english);
        printf("Overwriting existing data.\n");
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
    int total_rank = 1, english_rank = 1, math_rank = 1, science_rank = 1;

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

    if (student->score.english < node->student->score.english)
    {
        *english_rank += 1;
    }
    if (student->score.math < node->student->score.math)
    {
        *math_rank += 1;
    }
    if (student->score.science < node->student->score.science)
    {
        *science_rank += 1;
    }
    if (student_total_score < node_total_score)
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
        if (token[0] != 'K')
        {
            continue;
        }
        char *student_id = token;
        token = strtok(NULL, ",");
        double english = atof(token);
        token = strtok(NULL, ",");
        double math = atof(token);
        token = strtok(NULL, ",");
        double science = atof(token);
        Student *student = create_student(student_id, english, math, science);
        node = insert_student_node(node, student);
    }
    return node;
}

void save_student_node_to_csv(StudentNode *node, char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("file not found\n");
        return;
    }

    save_student_node_to_csv_recursive(node, fp);
    fclose(fp);
}

void save_student_node_to_csv_recursive(StudentNode *node, FILE *fp)
{
    if (node == NULL)
    {
        return;
    }
    save_student_node_to_csv_recursive(node->right, fp);
    save_student_node_to_csv_recursive(node->left, fp);
    fprintf(fp, "%s,%f,%f,%f\n", node->student->student_id, node->student->score.english, node->student->score.math, node->student->score.science);
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

void get_english_score_array(StudentNode *node, double *english_array, int *index)
{
    if (node == NULL)
    {
        return;
    }
    get_english_score_array(node->left, english_array, index);
    english_array[*index] = node->student->score.english;
    *index += 1;
    get_english_score_array(node->right, english_array, index);
}

void get_math_score_array(StudentNode *node, double *math_array, int *index)
{
    if (node == NULL)
    {
        return;
    }
    get_math_score_array(node->left, math_array, index);
    math_array[*index] = node->student->score.math;
    *index += 1;
    get_math_score_array(node->right, math_array, index);
}

void get_science_score_array(StudentNode *node, double *science_array, int *index)
{
    if (node == NULL)
    {
        return;
    }
    get_science_score_array(node->left, science_array, index);
    science_array[*index] = node->student->score.science;
    *index += 1;
    get_science_score_array(node->right, science_array, index);
}

void get_total_score_array(StudentNode *node, double *total_array, int *index)
{
    if (node == NULL)
    {
        return;
    }
    get_total_score_array(node->left, total_array, index);
    total_array[*index] = node->student->score.english + node->student->score.math + node->student->score.science;
    *index += 1;
    get_total_score_array(node->right, total_array, index);
}

void create_score_array(double *array, int *index, int size)
{
    array = malloc(sizeof(double) * size);
    *index = 0;
}

void destroy_score_array(double *array)
{
    free(array);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void swap(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
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

ScoreMinHeap *create_score_min_heap(ScoreMinHeap *heap, int k)
{
    heap = malloc(sizeof(ScoreMinHeap));
    heap->size = k;
    heap->index = 0;
    heap->student_scores = (StudentScore *)malloc(sizeof(StudentScore) * heap->size);

    for (int i = 0; i < heap->size; i++)
    {
        heap->student_scores[i].score = INT_MIN;
        strcpy(heap->student_scores[i].student_id, "not found");
    }
    return heap;
}

void destroy_score_min_heap(ScoreMinHeap *heap)
{
    free(heap->student_scores);
    free(heap);
}

ScoreMinHeap *insert_score_min_heap(ScoreMinHeap *heap, StudentScore *student_score)
{
    if (student_score->score < heap->student_scores[0].score)
    {
        return heap;
    }
    heap->student_scores[0].score = student_score->score;
    strcpy(heap->student_scores[0].student_id, student_score->student_id);
    heapify_score_min_heap(heap, 0);
    return heap;
}

ScoreMinHeap *swap_score_min_heap_index(ScoreMinHeap *heap, int i, int j)
{
    StudentScore temp = heap->student_scores[i];
    heap->student_scores[i] = heap->student_scores[j];
    heap->student_scores[j] = temp;
    return heap;
}

void heapify_score_min_heap(ScoreMinHeap *heap, int i)
{
    int min_index = i;
    int left_child_index = 2 * i + 1;
    int right_child_index = 2 * i + 2;

    if (left_child_index < heap->size && heap->student_scores[left_child_index].score < heap->student_scores[min_index].score)
    {
        min_index = left_child_index;
    }

    if (right_child_index < heap->size && heap->student_scores[right_child_index].score < heap->student_scores[min_index].score)
    {
        min_index = right_child_index;
    }

    if (i != min_index)
    {
        swap_score_min_heap_index(heap, i, min_index);
        heapify_score_min_heap(heap, min_index);
    }
}

void get_english_score_min_heap(ScoreMinHeap *heap, StudentNode *node)
{
    if (node == NULL)
    {
        return;
    }
    get_english_score_min_heap(heap, node->left);

    StudentScore temp;
    strcpy(temp.student_id, node->student->student_id);
    temp.score = node->student->score.english;
    heap = insert_score_min_heap(heap, &temp);

    get_english_score_min_heap(heap, node->right);
}

void get_math_score_min_heap(ScoreMinHeap *heap, StudentNode *node)
{
    if (node == NULL)
    {
        return;
    }
    get_math_score_min_heap(heap, node->left);

    StudentScore temp;

    strcpy(temp.student_id, node->student->student_id);
    temp.score = node->student->score.math;
    heap = insert_score_min_heap(heap, &temp);

    get_math_score_min_heap(heap, node->right);
}

void get_science_score_min_heap(ScoreMinHeap *heap, StudentNode *node)
{
    if (node == NULL)
    {
        return;
    }
    get_science_score_min_heap(heap, node->left);

    StudentScore temp;
    strcpy(temp.student_id, node->student->student_id);
    temp.score = node->student->score.science;

    heap = insert_score_min_heap(heap, &temp);

    get_science_score_min_heap(heap, node->right);
}

void get_total_score_min_heap(ScoreMinHeap *heap, StudentNode *node)
{
    if (node == NULL)
    {
        return;
    }
    get_total_score_min_heap(heap, node->left);

    StudentScore temp;
    strcpy(temp.student_id, node->student->student_id);
    temp.score = node->student->score.english + node->student->score.math + node->student->score.science;

    heap = insert_score_min_heap(heap, &temp);

    get_total_score_min_heap(heap, node->right);
}

void print_score_min_heap(ScoreMinHeap *heap)
{
    for (int i = 0; i < heap->size; i++)
    {
        printf("%s %lf\n", heap->student_scores[i].student_id, heap->student_scores[i].score);
    }
}