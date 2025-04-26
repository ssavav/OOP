//
// Created by gregory on 10.04.2021.
//

#ifndef LAB_02_SET_NODE_HPP
#define LAB_02_SET_NODE_HPP


namespace collections {
    template<ComparableType T>
    set_node<T>::set_node(const T &data) : set_node<T>() {
        this->data = data;
    }

    template<ComparableType T>
    set_node<T>::set_node(std::shared_ptr<set_node<T>> &node) : set_node<T>(node.data) {
        this->next = node.next;
    }

    template<ComparableType T>
    void set_node<T>::set(const T &value) {
        data = value;
    }

    template<ComparableType T>
    void set_node<T>::exclude() {
        if (next)
            next->prev = prev;

        if (prev)
            prev->next = next;

        set_null();
    }

    template<ComparableType T>
    void set_node<T>::set_next(const set_node<T> &node) {
        this->next = std::make_shared<set_node<T>>(node);
    }

    template<ComparableType T>
    void set_node<T>::set_next(const std::shared_ptr<set_node<T>> &node) {
        this->next = node;
    }

    template<ComparableType T>
    void set_node<T>::set_prev(const set_node<T> &node) {
        this->prev = std::make_shared<set_node<T>>(node);
    }

    template<ComparableType T>
    void set_node<T>::set_prev(const std::shared_ptr<set_node<T>> &node) {
        this->prev = node;
    }

    template<ComparableType T>
    void set_node<T>::set_null() {
        this->next = nullptr;
        this->prev = nullptr;
    }

    template<ComparableType T>
    T &set_node<T>::value() {
        return this->data;
    }

    template<ComparableType T>
    const T &set_node<T>::get() const {
        return this->data;
    }

    template<ComparableType T>
    std::shared_ptr<set_node<T>> set_node<T>::get_next() const {
        return next;
    }

    template<ComparableType T>
    std::shared_ptr<set_node<T>> set_node<T>::get_prev() const {
        return prev;
    }

    template<ComparableType T>
    bool set_node<T>::operator==(const std::shared_ptr<set_node<T>> &node) const {
        return this == node;
    }

    template<ComparableType T>
    bool set_node<T>::operator!=(const std::shared_ptr<set_node<T>> &node) const {
        return this != node;
    }

    template<ComparableType T>
    bool set_node<T>::operator<(const std::shared_ptr<set_node<T>> &node) const {
        return this->data < node.lock()->data;
    }
}// namespace collections

#endif//LAB_02_SET_NODE_HPP
