cmake_minimum_required(VERSION 3.19)
project(lab_02)

# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем отсутствующие определения для MinGW
if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    
    # Определения для исправления совместимости
    add_definitions(
        -DGTEST_HAS_PTHREAD=0
        -DGTEST_OS_WINDOWS=1
        -DGTEST_HAS_TR1_TUPLE=0
        -D_CRT_SECURE_NO_WARNINGS
    )
    
    # Создаем заглушку для gtest-port.h с исправлениями
    file(WRITE ${CMAKE_BINARY_DIR}/gtest_mingw_fix.h [[
        #pragma once
        #include <cstring>
        #include <io.h>
        #include <stdlib.h>
        #include <direct.h>

        // MSVC функции и их эквиваленты в MinGW
        #define _stricmp strcasecmp
        #define _strdup strdup
        #define _fileno fileno
        #define _wcsicmp wcscasecmp
        #define _exit exit
        #define _OUT_TO_STDERR 1
        #define _MAX_PATH 260

        // Заглушки для отсутствующих функций
        inline void _set_error_mode(int) {}
    ]])
    
    include_directories(BEFORE ${CMAKE_BINARY_DIR})
    include_directories("${PROJECT_SOURCE_DIR}/collections/set/test")
endif()

# Подключаем FetchContent для автоматической загрузки GTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.8.1  # старая версия, совместимая с MinGW
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)
# Отключаем предупреждение об uninitialized переменных в Google Test
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-maybe-uninitialized")
FetchContent_MakeAvailable(googletest)

enable_testing()

# Исходники тестов
set(TEST_SOURCES 
    main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/collections/base_collection.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/collections/set)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/collections/set/node)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/collections/set/test)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/collections/set/const_iterator)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/collections)

# Создаем и связываем исполняемый файл
add_executable(lab_02 ${TEST_SOURCES})
target_link_libraries(lab_02 PRIVATE gtest gtest_main)

# Регистрируем тесты
include(GoogleTest)
gtest_discover_tests(lab_02)