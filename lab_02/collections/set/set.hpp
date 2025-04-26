//
// Created by gregory on 10.04.2021.
//

#ifndef LAB_02_SET_HPP
#define LAB_02_SET_HPP

#include <chrono>
#include <ranges>

#include "set.h"
#include <errors.h>

namespace collections {
    // Конструкторы и деструктор
    template<ComparableType T>
    set<T>::set(const set<T> &list) : set() {
        std::ranges::for_each(list, [this, &list](const value_type& item) {
            node_pointer temp_node = nullptr;
            try {
                temp_node = node_pointer(new node_type);
            } catch (std::bad_alloc &error) {
                auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                throw bad_alloc_err(ctime(&t), __FILE__, typeid(list).name(), __FUNCTION__);
            }
            temp_node->set(item);
            append(temp_node);
        });
    }

    template<ComparableType T>
    set<T>::set(set<T> &&list) noexcept {
        size = list.size;
        head = list.head;
    }

    template<ComparableType T>
    set<T>::set(std::initializer_list<T> elems) : set() {
        std::ranges::for_each(elems, [this](const value_type& el) {
            node_pointer temp_node = nullptr;
            try {
                temp_node = node_pointer(new node_type);
            } catch (std::bad_alloc &error) {
                auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                throw bad_alloc_err(ctime(&t), __FILE__, typeid(set).name(), __FUNCTION__);
            }
            temp_node->set(el);
            append(temp_node);
        });
    }

    template<ComparableType T>
    set<T>::~set() {
        this->clear();
    }

    // Модификаторы (append)
    template<ComparableType T>
    bool set<T>::append(const T &value) noexcept(false) {
        node_pointer temp_node;

        try {
            temp_node = node_pointer(new node_type);
        } catch (std::bad_alloc &error) {
            auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            throw bad_alloc_err(ctime(&t), __FILE__, typeid(set).name(), __FUNCTION__);
        }

        temp_node->set(value);

        return append(temp_node);
    }

    template<ComparableType T>
    bool set<T>::append(T &&value) noexcept(false) {
        node_pointer temp_node;

        try {
            temp_node = node_pointer(new node_type);
        } catch (std::bad_alloc &error) {
            auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            throw bad_alloc_err(ctime(&t), __FILE__, typeid(set).name(), __FUNCTION__);
        }

        temp_node->set(value);

        return append(temp_node);
    }

    template<ComparableType T>
    bool set<T>::append(const node_pointer &node) noexcept(false) {
        node_pointer temp;

        try {
            temp = node_pointer(new node_type);
        } catch (std::bad_alloc &error) {
            auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            throw bad_alloc_err(ctime(&t), __FILE__, typeid(set).name(), __FUNCTION__);
        }

        temp->set(node->get());

        if (!size) {
            head = temp;
            tail = temp;
            size++;

            return true;
        }

        if (find(temp->get()))
            return false;

        temp->set_prev(tail);
        tail->set_next(temp);
        tail = temp;
        size++;

        return true;
    }

    template<ComparableType T>
    void set<T>::append(std::initializer_list<T> ilist) noexcept(false) {
        std::ranges::for_each(ilist, [this](const value_type& el) {
            node_pointer temp_node = nullptr;
            try {
                temp_node = node_pointer(new node_type);
            } catch (std::bad_alloc &error) {
                auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                throw bad_alloc_err(ctime(&t), __FILE__, typeid(set).name(), __FUNCTION__);
            }
            temp_node->set(el);
            append(temp_node);
        });
    }

    template<ComparableType T>
    void set<T>::append(T *ilist, size_t len) noexcept(false) {
        std::span<T> span(ilist, len);
        std::ranges::for_each(span, [this](const value_type& item) {
            append(item);
        });
    }

    // Модификаторы (update)
    template<ComparableType T>
    set<T> set<T>::update(const T &value) noexcept(false) {
        set<T> res(*this);
        res.append(value);
        return res;
    }

    template<ComparableType T>
    set<T> set<T>::update(T &&value) noexcept(false) {
        set<T> res(*this);
        res.append(value);
        return res;
    }

    template<ComparableType T>
    set<T> set<T>::update(std::initializer_list<T> ilist) noexcept(false) {
        set<T> res(*this);
        std::ranges::for_each(ilist, [&res](const value_type& el) {
            res.append(el);
        });
        return res;
    }

    template<ComparableType T>
    set<T> set<T>::update(T *ilist, size_t len) noexcept(false) {
        set<T> res(*this);
        std::span<T> span(ilist, len);
        std::ranges::for_each(span, [&res](const value_type& item) {
            res.append(item);
        });
        return res;
    }

    // Операции с множествами
    template<ComparableType T>
    set<T> set<T>::intersect(const set<T> &set) {
        return *this & set;
    }

    template<ComparableType T>
    set<T> set<T>::intersect(const T &data) {
        return *this & data;
    }

    template<ComparableType T>
    set<T> set<T>::combine(const set<T> &set) {
        return *this | set;
    }

    template<ComparableType T>
    set<T> set<T>::combine(const T &data) {
        return *this | data;
    }

    template<ComparableType T>
    set<T> set<T>::difference(const set<T> &set) {
        return *this - set;
    }

    template<ComparableType T>
    set<T> set<T>::difference(const T &data) {
        return *this - data;
    }

    template<ComparableType T>
    set<T> set<T>::symmetric_difference(const set<T> &set) {
        return *this ^ set;
    }

    template<ComparableType T>
    set<T> set<T>::symmetric_difference(const T &data) {
        return *this ^ data;
    }

    // Удаление элементов
    template<ComparableType T>
    void set<T>::erase(const T &value) {
        auto t = find(value);

        if (t)
            erase(t);
    }

    template<ComparableType T>
    void set<T>::erase(const_set_iterator<T> pos) {
        if (!size)
            return;

        if (!pos) {
            auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            throw iterator_error(ctime(&t), __FILE__, typeid(set).name(), __FUNCTION__);
        }

        auto t = std::make_shared<node_type>(pos.get_cur());

        if (head->get() == t->get())
            head = t->get_next();

        auto r = t->get_next();
        t->exclude();

        --size;
    }

    template<ComparableType T>
    void set<T>::clear() {
        while (head) {
            auto t = head;
            head = head->get_next();
            t->set_next(nullptr);

            t = tail;
            tail = tail->get_prev();
            t->set_prev(nullptr);
        }

        size = 0;
    }

    // Проверка на пустоту
    template<ComparableType T>
    bool set<T>::empty() const {
        return size == 0;
    }

    // Получение размера
    template<ComparableType T>
    size_t set<T>::get_size() {
        return size;
    }

    // Поиск
    template<ComparableType T>
    typename set<T>::const_iterator set<T>::find(const T &val) const {
        auto view = std::ranges::subrange(begin(), end());
        auto it = std::ranges::find_if(view, [&val](const value_type& el) { 
            return val == el; 
        });
        
        if (it != end())
            return it;
        
        return end();
    }

    // Операторы присваивания
    template<ComparableType T>
    set<T> &set<T>::operator=(const set<T> &list) {
        if (&list == this)
            return *this;
    
        this->clear();
        size = 0;
        head = nullptr;
        tail = nullptr;
    
        std::ranges::for_each(list, [this, &list](const value_type& item) {
            node_pointer temp_node = nullptr;
            try {
                temp_node = node_pointer(new node_type);
            } catch (std::bad_alloc &error) {
                auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                throw bad_alloc_err(ctime(&t), __FILE__, typeid(list).name(), __FUNCTION__);
            }
            temp_node->set(item);
            append(temp_node);
        });
    
        return *this;
    }

    template<ComparableType T>
    set<T> &set<T>::operator=(set<T> &&list) noexcept {
        size = list.size;
        head = list.head;
        tail = list.tail;

        return *this;
    }

    // Операторы сравнения
    template<ComparableType T>
    bool set<T>::operator==(const set<T> &list) const {
        if (size != list.size)
            return false;
    
        return std::ranges::all_of(list, [this](const value_type& i) {
            return this->find(i) != this->end();
        });
    }

    template<ComparableType T>
    bool set<T>::operator!=(const set<T> &list) const {
        return !(*this == list);
    }

    // Операторы для работы с множествами
    template<ComparableType T>
    set<T> set<T>::operator+(const set<T> &ds) {
        set<T> s{*this};
        s += ds;
        return s;
    }

    template<ComparableType T>
    set<T> set<T>::operator+(const T &data) {
        set<T> s{*this};
        s += data;
        return s;
    }

    template<ComparableType T>
    set<T> set<T>::operator&(const set<T> &data) {
        set<T> res;

        auto iter1 = this->begin(), iter2 = data.begin();
        while (iter1 and iter2) {
            if (*iter1 == *iter2) {
                res.append(*iter1);
                ++iter1;
                ++iter2;
            } else if (*iter1 < *iter2) {
                ++iter1;
            } else {
                ++iter2;
            }
        }

        return res;
    }

    template<ComparableType T>
    set<T> set<T>::operator&(const T &data) {
        if (this->find(data))
            return set<T>{data};

        return set<T>();
    }

    template<ComparableType T>
    set<T> set<T>::operator|(const set<T> &set) {
        return *this + set;
    }

    template<ComparableType T>
    set<T> set<T>::operator|(const T &data) {
        return *this + data;
    }

    template<ComparableType T>
    set<T> set<T>::operator-(const set<T> &data) {
        set<T> res;
    
        std::ranges::for_each(*this, [&res](const value_type& i) {
            res.append(i);
        });
    
        std::ranges::for_each(data, [&res](const value_type& i) {
            res.erase(i);
        });
    
        return res;
    }

    template<ComparableType T>
    set<T> set<T>::operator-(const T &data) {
        set<T> res = *this;
        res.erase(data);

        return res;
    }

    template<ComparableType T>
    set<T> set<T>::operator^(const set<T> &data) {
        set<T> res;
    
        std::ranges::for_each(*this, [&res, &data](const value_type& i) {
            if (!data.find(i))
                res.append(i);
        });
    
        std::ranges::for_each(data, [&res, this](const value_type& i) {
            if (!this->find(i))
                res.append(i);
        });
    
        return res;
    }

    template<ComparableType T>
    set<T> set<T>::operator^(const T &data) {
        set<T> res = *this;
        if (res.find(data))
            res.erase(data);
        else
            res.append(data);

        return res;
    }

    // Операторы сложного присваивания
    template<ComparableType T>
    set<T> &set<T>::operator+=(const set<T> &list) {
        std::ranges::for_each(list, [this](const value_type& item) {
            append(item);
        });
    
        return *this;
    }

    template<ComparableType T>
    set<T> &set<T>::operator+=(const T &data) {
        append(data);
        return *this;
    }

    template<ComparableType T>
    set<T> &set<T>::operator&=(const set<T> &list) {
        set<T> res;
        
        // Первый цикл труднее напрямую перевести на ranges, так как используется
        // два параллельных итератора с логикой сравнения
        // Можно использовать вспомогательную функцию
        auto merge_intersection = [&res](const auto& a, const auto& b) {
            auto iter1 = a.begin(), iter2 = b.begin();
            while (iter1 && iter2) {
                if (*iter1 == *iter2) {
                    res.append(*iter1);
                    ++iter1;
                    ++iter2;
                } else if (*iter1 < *iter2) {
                    ++iter1;
                } else {
                    ++iter2;
                }
            }
        };
        
        merge_intersection(*this, list);
        
        this->clear();
        
        // Второй цикл легко заменяется на ranges
        std::ranges::for_each(res, [this](const value_type& i) {
            this->append(i);
        });
        
        return *this;
    }
    
    template<ComparableType T>
    set<T> &set<T>::operator&=(const T &data) {
        if (!find(data)) {
            clear();
        } else {
            clear();
            append(data);
        }

        return *this;
    }

    template<ComparableType T>
    set<T> &set<T>::operator|=(const set<T> &set) {
        *this += set;

        return *this;
    }

    template<ComparableType T>
    set<T> &set<T>::operator|=(const T &data) {
        *this += data;

        return *this;
    }

    template<ComparableType T>
    set<T> &set<T>::operator-=(const set<T> &set) {
        std::ranges::for_each(set, [this](const value_type& i) {
            erase(i);
        });
    
        return *this;
    }

    template<ComparableType T>
    set<T> &set<T>::operator-=(const T &data) {
        erase(data);

        return *this;
    }

    template<ComparableType T>
    set<T> &set<T>::operator^=(const set<T> &list) {
        set<T> temp = *this ^ list;
        clear();
        
        std::ranges::for_each(temp, [this](const value_type& i) {
            append(i);
        });
    
        return *this;
    }

    template<ComparableType T>
    set<T> &set<T>::operator^=(const T &data) {
        if (!find(data))
            append(data);
        else
            erase(data);

        return *this;
    }

    // Операторы вывода
    template<ComparableType T>
    std::ostream &operator<<(std::ostream &os, set<T> &list) {
        std::ranges::for_each(list.begin(), list.end(), [&os](const T& el) {
            os << el << " ";
        });
    
        return os;
    }
    
    template<ComparableType T>
    std::ostream &operator<<(std::ostream &os, const set<T> &list) {
        std::ranges::for_each(list.begin(), list.end(), [&os](const T& el) {
            os << el << " ";
        });
    
        return os;
    }

    // Итераторы
    template<ComparableType T>
    typename set<T>::const_iterator set<T>::begin() const {
        return const_iterator(head);
    }

    template<ComparableType T>
    typename set<T>::const_iterator set<T>::end() const {
        return const_iterator(tail ? tail->get_next() : nullptr);
    }
}// namespace collections

#endif//LAB_02_SET_HPP
