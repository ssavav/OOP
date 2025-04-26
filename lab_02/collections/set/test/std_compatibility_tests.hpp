//
// Created on 25.04.2025.
//

#ifndef LAB_02_STD_COMPATIBILITY_TESTS_HPP
#define LAB_02_STD_COMPATIBILITY_TESTS_HPP

#include <gtest/gtest.h>
#include <set.h>
#include <set>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <algorithm>
#include <iostream>

using namespace collections;

// Тест на совместимость с функциями, принимающими итераторы разных типов множеств
TEST(StdCompatibilityTest, IteratorCompatibility) {
    // Создаём оба множества с одинаковыми значениями
    collections::set<int> coll_set{1, 2, 3, 4, 5};
    std::set<int> std_set{1, 2, 3, 4, 5};

    // Используем алгоритм copy чтобы проверить, что итераторы работают корректно
    std::vector<int> coll_result;
    std::vector<int> std_result;
    
    std::copy(coll_set.begin(), coll_set.end(), std::back_inserter(coll_result));
    std::copy(std_set.begin(), std_set.end(), std::back_inserter(std_result));
    
    // Оба должны содержать одинаковые элементы в одинаковом порядке (отсортированном)
    ASSERT_EQ(coll_result.size(), std_result.size());
    for (size_t i = 0; i < coll_result.size(); ++i) {
        EXPECT_EQ(coll_result[i], std_result[i]);
    }
}

// Тест на конвертацию из std::set в collections::set
TEST(StdCompatibilityTest, ConversionFromStdSet) {
    std::set<int> std_set{1, 2, 3, 4, 5};
    collections::set<int> coll_set;
    
    // Заполняем наше множество из стандартного
    for (const auto& element : std_set) {
        coll_set.append(element);
    }
    
    // Проверяем, что все элементы скопированы
    EXPECT_EQ(coll_set.get_size(), std_set.size());
    for (const auto& element : std_set) {
        EXPECT_NE(coll_set.find(element), coll_set.end());
    }
}

// Тест на конвертацию из collections::set в std::set
TEST(StdCompatibilityTest, ConversionToStdSet) {
    collections::set<int> coll_set{1, 2, 3, 4, 5};
    std::set<int> std_set;
    
    // Заполняем стандартное множество из нашего
    for (const auto& element : coll_set) {
        std_set.insert(element);
    }
    
    // Проверяем, что все элементы скопированы
    EXPECT_EQ(std_set.size(), coll_set.get_size());
    for (const auto& element : coll_set) {
        EXPECT_NE(std_set.find(element), std_set.end());
    }
}

// Тест на использование операций с множествами между разными типами множеств
TEST(StdCompatibilityTest, SetOperationsAdapter) {
    collections::set<int> coll_set1{1, 2, 3, 4, 5};
    std::set<int> std_set1{4, 5, 6, 7, 8};
    collections::set<int> result;
    
    // Пример адаптера для операции объединения
    auto set_union_adapter = [](const collections::set<int>& coll_set, const std::set<int>& std_set) {
        collections::set<int> result = coll_set; // Копируем элементы из первого множества
        // Добавляем элементы из второго множества
        for (const auto& element : std_set) {
            result.append(element);
        }
        return result;
    };
    
    result = set_union_adapter(coll_set1, std_set1);
    
    // Результат должен содержать элементы обоих множеств
    EXPECT_NE(result.find(1), result.end());
    EXPECT_NE(result.find(4), result.end());
    EXPECT_NE(result.find(8), result.end());
    EXPECT_EQ(result.get_size(), 8); // 1,2,3,4,5,6,7,8
}

// Тест на поиск элементов в обоих типах множеств
TEST(StdCompatibilityTest, FindElements) {
    collections::set<int> coll_set{1, 2, 3, 4, 5};
    std::set<int> std_set{1, 2, 3, 4, 5};
    
    // Проверяем, что элементы находятся как в нашем множестве, так и в стандартном
    for (int i = 1; i <= 5; ++i) {
        // В нашем множестве используем find
        auto coll_it = coll_set.find(i);
        EXPECT_NE(coll_it, coll_set.end());
        
        // В std::set используем find
        auto std_it = std_set.find(i);
        EXPECT_NE(std_it, std_set.end());
        
        // Значения должны совпадать
        EXPECT_EQ(*coll_it, *std_it);
    }
}

// Функция для печати содержимого множества
template<typename T>
void print_set(const collections::set<T>& s) {
    for (const auto& item : s) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

// Демонстрационная функция для совместимости с STL контейнерами
void demonstrate_stl_compatibility() {
    std::cout << "\n=== Демонстрация совместимости с STL контейнерами ===\n";
    
    // 1. Создание множества из разных STL контейнеров
    std::cout << "1. Создание множества из разных STL контейнеров:\n";
    
    // Из std::vector
    std::vector<int> vec = {1, 2, 3, 2, 1};
    collections::set<int> set1;
    for (const auto& item : vec) {
        set1.append(item);
    }
    std::cout << "   Из std::vector {1, 2, 3, 2, 1}: ";
    print_set(set1);
    
    // Из std::list
    std::list<int> lst = {4, 5, 6, 5, 4};
    collections::set<int> set2;
    for (const auto& item : lst) {
        set2.append(item);
    }
    std::cout << "   Из std::list {4, 5, 6, 5, 4}: ";
    print_set(set2);
    
    // Из std::set
    std::set<int> std_set = {7, 8, 9};
    collections::set<int> set3;
    for (const auto& item : std_set) {
        set3.append(item);
    }
    std::cout << "   Из std::set {7, 8, 9}: ";
    print_set(set3);
    
    // 2. Операции над множествами из разных контейнеров
    std::cout << "\n2. Операции над множествами из разных контейнеров:\n";
    
    // Объединение set1 с std::vector
    std::vector<int> vec2 = {3, 4, 5};
    collections::set<int> union_result = set1;
    for (const auto& item : vec2) {
        union_result.append(item);
    }
    std::cout << "   Объединение с вектором {3, 4, 5}: ";
    print_set(union_result);
    
    // Пересечение set1 с std::set
    std::set<int> std_set2 = {1, 3, 5};
    collections::set<int> intersect_result;
    for (const auto& item : set1) {
        if (std_set2.find(item) != std_set2.end()) {
            intersect_result.append(item);
        }
    }
    std::cout << "   Пересечение с std::set {1, 3, 5}: ";
    print_set(intersect_result);
    
    // 3. Преобразование множества в STL контейнеры
    std::cout << "\n3. Преобразование множества в STL контейнеры:\n";
    
    // В std::vector
    std::vector<int> result_vec;
    for (const auto& item : set1) {
        result_vec.push_back(item);
    }
    std::cout << "   В std::vector: ";
    for (const auto& item : result_vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    // В std::set
    std::set<int> result_std_set;
    for (const auto& item : set1) {
        result_std_set.insert(item);
    }
    std::cout << "   В std::set: ";
    for (const auto& item : result_std_set) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    // 4. Использование алгоритмов STL с нашим множеством
    std::cout << "\n4. Использование алгоритмов STL с нашим множеством:\n";
    
    // Поиск с помощью std::find_if
    auto it = std::find_if(set1.begin(), set1.end(), [](int x) { return x > 1; });
    std::cout << "   std::find_if (первый элемент > 1): " << *it << std::endl;
    
    // Подсчет элементов с помощью std::count_if
    int count = std::count_if(set1.begin(), set1.end(), [](int x) { return x % 2 == 0; });
    std::cout << "   std::count_if (количество четных): " << count << std::endl;
    
    // Преобразование с помощью std::transform
    std::vector<int> transformed;
    std::transform(set1.begin(), set1.end(), std::back_inserter(transformed), 
                  [](int x) { return x * 2; });
    std::cout << "   std::transform (умножение на 2): ";
    for (const auto& item : transformed) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    // 5. Комбинированные операции множеств
    std::cout << "\n5. Комбинированные операции множеств:\n";
    
    collections::set<int> combined1 = set1;
    collections::set<int> combined2 = set2;
    
    // Объединение
    collections::set<int> union_set = combined1;
    union_set |= combined2;
    std::cout << "   Объединение set1 и set2: ";
    print_set(union_set);
    
    // Разность
    collections::set<int> diff_set = combined1;
    diff_set -= combined2;
    std::cout << "   Разность set1 - set2: ";
    print_set(diff_set);
    
    // Симметрическая разность
    collections::set<int> sym_diff_set = combined1;
    sym_diff_set ^= combined2;
    std::cout << "   Симметрическая разность set1 ^ set2: ";
    print_set(sym_diff_set);
    
    // 6. Работа с разными типами данных
    std::cout << "\n6. Работа с разными типами данных:\n";
    
    collections::set<std::string> str_set;
    str_set.append("apple");
    str_set.append("banana");
    str_set.append("cherry");
    
    std::cout << "   Строковое множество: ";
    print_set(str_set);
    
    // Проверка на вхождение элемента, аналогично std::set
    std::cout << "   Поиск 'banana': " 
              << (str_set.find("banana") != str_set.end() ? "найдено" : "не найдено") << std::endl;
    std::cout << "   Поиск 'grape': " 
              << (str_set.find("grape") != str_set.end() ? "найдено" : "не найдено") << std::endl;
}

// Добавляем тест, который вызывает демонстрационную функцию
TEST(StlCompatibilityDemo, DemonstrateCompatibility) {
    // Этот тест будет просто выводить информацию, а не проверять условия
    // Поэтому используем фиктивное EXPECT_TRUE
    demonstrate_stl_compatibility();
    EXPECT_TRUE(true);
}

#endif//LAB_02_STD_COMPATIBILITY_TESTS_HPP