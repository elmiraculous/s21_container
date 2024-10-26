#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <limits>
namespace s21
{
    template <typename T>
    class Vector
    {
    private:
        size_t m_size;
        size_t m_capacity;
        T *arr;

    public:
        // сам тип элементов
        using value_type = T;
        // псевдоним для ссылки на элемент контейнера
        using reference = T &;
        // ссылка на элемент контейнера
        using const_reference = const T &;
        //  количества элементов в контейнере
        using size_type = size_t;
        using iterator = T *;
        using const_iterator = const T *;

        // конструкторы
        Vector();
        explicit Vector(size_type n);
        Vector(std::initializer_list<value_type> const &items);
        Vector(const Vector &v);
        Vector(Vector &&v);
        Vector &operator=(Vector &&v);
        ~Vector();

        reference at(size_type pos);
        reference operator[](size_type pos);
        const_reference front();
        const_reference back();
        T *data();

        iterator begin(); // Итератор на начало
        iterator end();   // Итератор на конец

        bool empty() const;
        size_type size() const;
        size_type max_size() const;
        void reserve(size_type new_capacity);
        size_type capacity() const;
        void shrink_to_fit();

        void clear();
        iterator insert(iterator pos, const_reference value);
        void erase(iterator pos);
        void push_back(const_reference value);
        void pop_back();
        void swap(Vector &other);
    };
}
#include "s21_vector.tpp"

#endif
