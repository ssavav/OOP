//
// Created on 25.04.2023.
//

#ifndef LAB_02_CONCEPTS_H
#define LAB_02_CONCEPTS_H

#include <concepts>

namespace collections {
    // Определяем концепт для типа, который может использоваться в множестве
    template<typename T>
    concept ComparableType = std::default_initializable<T> &&
                            std::copy_constructible<T> &&
                            std::movable<T> &&
                            requires(const T& a, const T& b) {
                                { a == b } -> std::convertible_to<bool>;
                                { a != b } -> std::convertible_to<bool>;
                                { a < b } -> std::convertible_to<bool>;
                            };
}

#endif//LAB_02_CONCEPTS_H