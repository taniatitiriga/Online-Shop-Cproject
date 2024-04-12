cmake_minimum_required(VERSION 3.27)
project(Online_Shop_Cproject C)

set(CMAKE_C_STANDARD 11)

add_executable(Online_Shop_Cproject
        main.c
        shop.h
        shop.c
        product.h
        order.h
        constants.h
        fileIO.h
        fileIO.c)
