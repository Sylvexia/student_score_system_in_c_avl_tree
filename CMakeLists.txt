cmake_minimum_required(VERSION 3.1.0)
project(student_score_linked_list C)

add_library(
    database_lib
    database.c
    database.h
)

add_library(
    user_interface_lib
    user_interface.c
    user_interface.h
)

add_executable(student_score_linked_list main.c)

target_link_libraries(student_score_linked_list database_lib user_interface_lib)