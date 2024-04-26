cmake_minimum_required(VERSION 3.27)
project(Online_Shop_Cproject C)

set(CMAKE_C_STANDARD 11)

add_executable(Online_Shop_Cproject
        main.c
        account.h
        account.c
        file.h
        file.c)