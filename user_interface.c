#include "user_interface.h"

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

            /// debug features
        case INSERT_RAND_DATA:
            feature_add_rand_data(student_node);
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

    Student *new_student = create_student(student_id, english, math, science);
    student_node = insert_student_node(student_node, new_student);

    return student_node;
}

StudentNode *feature_load_from_csv(StudentNode *student_node)
{
    char file_name[FILE_NAME_LENGTH];

    user_insert_file_name(file_name);

    student_node = load_student_node_from_csv(student_node, file_name);

    return student_node;
}

void feature_log_student_data_by_id(StudentNode *student_node)
{
    print_student_node_inorder(student_node);

    return;
}

void feature_search_by_id_evaluate(StudentNode *student_node)
{
    char student_id[STUDENT_ID_LENGTH + 1];
    user_insert_student_id(student_id);

    StudentNode *target_node = search_student_node(student_node, student_id);
    if (target_node == NULL)
    {
        printf("student not found\n");
        return;
    }

    print_student_evaluate(student_node, target_node->student);

    return;
}

void feature_search_top_ten_score_by_subject(StudentNode *student_node)
{
    printf("top ten score by specific subject\n");
    return;
}

void feature_search_top_ten_score_by_total_score(StudentNode *student_node)
{
    printf("top ten score by total score\n");
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
        user_insert_student_id(student_id);
        user_insert_student_score(&english, &math, &science);
        student_node = insert_student_node(student_node, create_student(student_id, english, math, science));
        break;

    case 2:
        user_insert_student_id(student_id);
        student_node = delete_student_node(student_node, student_id);

    default:
        printf("input error\n");
        break;
    }

    return student_node;
}

void feature_add_rand_data(StudentNode *student_node)
{
    printf("add rand data\n");
    return;
}

void feature_save_csv(StudentNode *student_node)
{
    printf("save csv\n");
    return;
}