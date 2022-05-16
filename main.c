#include <stdio.h>
#include <stdlib.h>
#include "user_interface.h"

int main()
{
    StudentNode *root = NULL;
    root = insert_student_node(root, create_student("123456789", 90, 80, 70));
    root = insert_student_node(root, create_student("987654321", 80, 70, 60));
    root = insert_student_node(root, create_student("111111111", 70, 60, 50));
    root = insert_student_node(root, create_student("222222222", 60, 50, 40));
    root = insert_student_node(root, create_student("333333333", 50, 40, 30));
    root = insert_student_node(root, create_student("444444444", 40, 30, 20));
    print_student_node(root);
}
