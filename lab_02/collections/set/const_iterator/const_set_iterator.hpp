//
// Created by gregory on 12.04.2021.
//

#ifndef LAB_02_CONST_SET_ITERATOR_HPP
#define LAB_02_CONST_SET_ITERATOR_HPP

namespace collections {
    template<ComparableType T>
    const_set_iterator<T>::const_set_iterator() {
        this->cur.lock() = nullptr;
    }

    template<ComparableType T>
    const_set_iterator<T>::const_set_iterator(const std::shared_ptr<set_node<T>> &node) {
        this->cur = node;
    }

    template<ComparableType T>
    const_set_iterator<T>::const_set_iterator(const const_set_iterator<T> &iterator) {
        this->cur = iterator.cur.lock();
    }

    template<ComparableType T>
    void const_set_iterator<T>::set_cur(set_node<T> &node) {
        this->set_cur(node);
    }

    template<ComparableType T>
    set_node<T> &const_set_iterator<T>::get_cur() {
        return *this->cur.lock();
    }

    template<ComparableType T>
    set_node<T> &const_set_iterator<T>::get_cur() const {
        return *this->cur.lock();
    }

    template<ComparableType T>
    void const_set_iterator<T>::next() {
        this->cur = get_cur().get_next();
    }

    template<ComparableType T>
    void const_set_iterator<T>::prev() {
        this->cur = get_cur().get_prev();
    }

    template<ComparableType T>
    const T *const_set_iterator<T>::operator->() const {
        return get_cur().get();
    }

    template<ComparableType T>
    const T &const_set_iterator<T>::operator*() const {
        return get_cur().value();
    }

    template<ComparableType T>
    const_set_iterator<T>::operator bool() const {
        return nullptr != this->cur.lock();
    }

    template<ComparableType T>
    const_set_iterator<T> &const_set_iterator<T>::operator=(const const_set_iterator<T> &iterator) {
        this->cur = iterator.cur.lock();
        return *this;
    }

    template<ComparableType T>
    const_set_iterator<T> &const_set_iterator<T>::operator++() {
        this->next();
        return *this;
    }

    template<ComparableType T>
    const collections::const_set_iterator<T> collections::const_set_iterator<T>::operator++(int) {
        const_set_iterator<T> tmp = *this;
        this->next();
        return tmp;
    }

    template<ComparableType T>
    const_set_iterator<T> &const_set_iterator<T>::operator--() {
        this->prev();
        return *this;
    }

    template<ComparableType T>
    const const_set_iterator<T> collections::const_set_iterator<T>::operator--(int) {
        const_set_iterator<T> tmp = *this;
        this->prev();
        return tmp;
    }

    template<ComparableType T>
    bool const_set_iterator<T>::operator!=(const const_set_iterator<T> &iterator) const {
        return this->cur.lock() != iterator.cur.lock();
    }

    template<ComparableType T>
    bool const_set_iterator<T>::operator==(const const_set_iterator<T> &iterator) const {
        return this->cur.lock() == iterator.cur.lock();
    }
}// namespace collections

#endif//LAB_02_CONST_SET_ITERATOR_HPP
