#include "user_interface.h"

#include <time.h>

void print_manual()
{
    printf("input the number according to the feature:\n");
    printf("1. insert single student data, if exist, overwrite\n");
    printf("2. load from csv\n");
    printf("3. logging the student data, sorted by id\n");
    printf("4. search by specific student id, list all subject score, total score, average, rank from all subjects, rank by total score\n");
    printf("5. search top 10 score by specific subject\n");
    printf("6. search top 10 score by total score\n");
    printf("7. add, delete student data\n");
    printf("8. exit\n");
    printf("other number may be features for debug UwU\n");
    printf("input the number: \n");
}

void user_interface()
{
    int exit = 0;
    StudentNode *student_node = NULL;

    while (!exit)
    {
        enum FEATURES feature = 0;
        int feature_id = (int)feature;

        printf("memory allocated: %f MB\n", (double)get_size(student_node) * sizeof(student_node) / 1048576);
        print_manual();
        scanf("%d", &feature_id);

        switch (feature_id)
        {
        case INSERT_SINGLE_STUDENT:
            student_node = feature_insert_student_data(student_node);
            break;
        case LOAD_CSV:
            student_node = feature_load_from_csv(student_node);
            break;
        case LOG_SORTED_BY_ID:
            feature_log_student_data_by_id(student_node);
            break;
        case SEARCH_BY_ID_EVALUATE:
            feature_search_by_id_evaluate(student_node);
            break;
        case SEARCH_TOP_TEN_SPECIFIC_SUBJECT:
            feature_search_top_ten_score_by_subject(student_node);
            break;
        case SEARCH_TOP_TEN_TOTAL_SCORE:
            feature_search_top_ten_score_by_total_score(student_node);
            break;
        case ADD_DELETE_STUDENT:
            student_node = feature_add_delete_student_data(student_node);
            break;
        case EXIT:
            exit = 1;
            destroy_student_node(student_node);
            break;

            // debug features
        case INSERT_RAND_DATA:
            student_node = feature_add_rand_data(student_node);
            break;
        case SAVE_CSV:
            feature_save_csv(student_node);
            break;
        default:
            printf("input error\n");
            break;
        }
    }
}

void user_insert_student_id(char *student_id)
{
    printf("input student id: \n");
    scanf("%s", student_id);

    return;
}

void user_insert_student_score(double *english, double *math, double *science)
{
    printf("input english score: \n");
    scanf("%lf", english);
    printf("input math score: \n");
    scanf("%lf", math);
    printf("input science score: \n");
    scanf("%lf", science);

    return;
}

void user_insert_file_name(char *file_name)
{
    printf("input file name: \n");
    scanf("%s", file_name);

    return;
}

StudentNode *feature_insert_student_data(StudentNode *student_node)
{
    char student_id[STUDENT_ID_LENGTH + 1];
    double english, math, science = 0;

    user_insert_student_id(student_id);
    user_insert_student_score(&english, &math, &science);

    // start time
    clock_t start = clock();

    Student *new_student = create_student(student_id, english, math, science);
    student_node = insert_student_node_with_overwrite_log(student_node, new_student);

    // end time
    clock_t end = clock();
    printf("elapsed seconds: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    return student_node;
}

StudentNode *feature_load_from_csv(StudentNode *student_node)
{
    char file_name[FILE_NAME_LENGTH];

    user_insert_file_name(file_name);

    // start time
    clock_t start = clock();

    student_node = load_student_node_from_csv(student_node, file_name);

    // end time
    clock_t end = clock();
    printf("elapsed seconds: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    return student_node;
}

void feature_log_student_data_by_id(StudentNode *student_node)
{
    // start time
    clock_t start = clock();

    print_student_node_inorder(student_node);

    // end time
    clock_t end = clock();
    printf("elapsed seconds: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    return;
}

void feature_search_by_id_evaluate(StudentNode *student_node)
{
    char student_id[STUDENT_ID_LENGTH + 1];
    user_insert_student_id(student_id);

    // start time
    clock_t start = clock();

    StudentNode *target_node = search_student_node(student_node, student_id);
    if (target_node == NULL)
    {
        printf("student not found\n");
        // end time
        clock_t end = clock();
        printf("elapsed seconds: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
        return;
    }

    print_student_evaluate(student_node, target_node->student);

    // end time
    clock_t end = clock();
    printf("elapsed seconds: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    return;
}

void feature_search_top_ten_score_by_subject(StudentNode *student_node)
{
    Subject subject = 0;
    int subject_id = (int)subject;
    printf("insert subject number\n");
    printf("1. english\n");
    printf("2. math\n");
    printf("3. science\n");
    scanf("%d", &subject_id);

    // start time
    clock_t start = clock();

    ScoreMinHeap *heap = create_score_min_heap(heap, 10);

    switch (subject_id)
    {
    case ENGLISH:
        get_english_score_min_heap(heap, student_node);
        break;

    case MATH:
        get_math_score_min_heap(heap, student_node);
        break;

    case SCIENCE:
        get_science_score_min_heap(heap, student_node);
        break;
    }
    print_score_min_heap(heap);

    destroy_score_min_heap(heap);

    // end time
    clock_t end = clock();
    printf("elapsed seconds: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    return;
}

void feature_search_top_ten_score_by_total_score(StudentNode *student_node)
{
    // start time
    clock_t start = clock();

    ScoreMinHeap *heap = create_score_min_heap(heap, 10);
    get_total_score_min_heap(heap, student_node);
    print_score_min_heap(heap);

    destroy_score_min_heap(heap);

    // end time
    clock_t end = clock();
    printf("elapsed seconds: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    return;
}

StudentNode *feature_add_delete_student_data(StudentNode *student_node)
{
    char student_id[STUDENT_ID_LENGTH + 1];
    double english, math, science = 0;
    int choice = 0;

    printf("1. add student data\n");
    printf("2. delete student data\n");
    printf("input the number: \n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        user_insert_student_id(student_id);
        user_insert_student_score(&english, &math, &science);

        // start time
        clock_t start = clock();

        student_node = insert_student_node(student_node, create_student(student_id, english, math, science));

        // end time
        clock_t end = clock();
        printf("elapsed seconds: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

        break;
    }
    case 2:
    {
        user_insert_student_id(student_id);

        // start time
        clock_t start = clock();
        student_node = delete_student_node(student_node, student_id);

        // end time
        clock_t end = clock();
        printf("elapsed seconds: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

        break;
    }
    default:
        printf("input error\n");
        break;
    }

    return student_node;
}

StudentNode *feature_add_rand_data(StudentNode *student_node)
{
    int n = 0;
    printf("input number of random student data: \n");
    scanf("%d", &n);

    // start time
    clock_t start = clock();

    for (int i = 0; i < n; i++)
    {
        char student_id[STUDENT_ID_LENGTH + 1];
        double english, math, science = 0;
        // generate id : KXXXXXXXXX
        student_id[0] = 'K';

        for (int j = 1; j < STUDENT_ID_LENGTH; j++)
        {
            student_id[j] = rand() % 10 + '0';
        }

        student_id[STUDENT_ID_LENGTH] = '\0';

        english = rand() % 1000 + rand() % 1000 / 1000.0;
        math = rand() % 1000 + rand() % 1000 / 1000.0;
        science = rand() % 1000 + rand() % 1000 / 1000.0;
        student_node = insert_student_node(student_node, create_student(student_id, english, math, science));
    }

    // end time
    clock_t end = clock();
    printf("elapsed seconds: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    return student_node;
}

void feature_save_csv(StudentNode *student_node)
{
    char file_name[FILE_NAME_LENGTH];
    // current time as file name
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    strftime(file_name, sizeof(file_name), "%Y%m%d%H%M%S.csv", &tm);

    printf("save file name: %s\n", file_name);
    save_student_node_to_csv(student_node, file_name);
    printf("save complete\n");

    return;
}
