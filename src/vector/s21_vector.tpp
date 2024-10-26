
namespace s21
{
    // Конструктор по умолчанию
    template <typename T>
    Vector<T>::Vector() : m_size(0), m_capacity(0), arr(nullptr) {}

    // Конструктор с параметром
    template <typename T>
    Vector<T>::Vector(size_type n)
        : m_size(n), m_capacity(n), arr(n ? new T[n] : nullptr) {}

    // Конструктор копирования
    template <typename T>
    Vector<T>::Vector(const Vector &v)
        : m_size(v.m_size), m_capacity(v.m_capacity), arr(new T[v.m_size])
    {
        for (size_type i = 0; i < m_size; ++i)
        {
            arr[i] = v.arr[i];
        }
    }

    // конструктор перемещения
    template <typename T>
    Vector<T>::Vector(Vector &&v)
        : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr)
    {
        v.arr = nullptr;
        v.m_size = 0;
        v.m_capacity = 0;
    }

    template <typename T>
    Vector<T> &Vector<T>::operator=(Vector &&v)
    {
        if (this != &v)
        {
            delete[] arr;

            arr = v.arr;
            m_size = v.m_size;
            m_capacity = v.m_capacity;

            v.arr = nullptr;
            v.m_size = 0;
            v.m_capacity = 0;
        }
        return *this;
    }
    template <typename T>
    typename Vector<T>::reference &Vector<T>::at(size_type pos)
    {
        if (pos >= m_size)
        {
            throw std::out_of_range("Index out of range");
        }
        return arr[pos];
    }

    template <typename T>
    typename Vector<T>::reference &Vector<T>::operator[](size_type pos)
    {
        if (pos >= m_size)
        {
            throw std::out_of_range("Index out of range");
        }
        return arr[pos];
    }
    // первый элемент
    template <typename T>
    typename Vector<T>::const_reference &Vector<T>::front()
    {
        if (!m_size)
        {
            throw std::out_of_range("Vector is empty");
        }
        return arr[0];
    }

    // последний элемент
    template <typename T>
    typename Vector<T>::const_reference &Vector<T>::back()
    {
        if (!m_size)
        {
            throw std::out_of_range("Vector is empty");
        }
        return arr[m_size - 1];
    }

    template <typename T>
    T *Vector<T>::data()
    {
        return arr;
    }

    template <typename T>
    bool Vector<T>::empty() const
    {
        return m_size == 0;
    }

    template <typename T>
    typename Vector<T>::size_type Vector<T>::size() const
    {
        return m_size;
    }

    template <typename T>
    typename Vector<T>::size_type Vector<T>::capacity() const
    {
        return m_capacity;
    }

    template <typename T>
    void Vector<T>::clear()
    {
        delete[] arr;
        arr = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    // Деструктор
    template <typename T>
    Vector<T>::~Vector()
    {
        delete[] arr;
    }

    template <typename T>
    typename Vector<T>::iterator Vector<T>::begin()
    {
        return arr;
    }

    template <typename T>
    typename Vector<T>::iterator Vector<T>::end()
    {
        return arr + m_size;
    }

    template <typename T>
    typename Vector<T>::size_type Vector<T>::max_size() const
    {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    template <typename T>
    void Vector<T>::reserve(size_type new_capacity)
    {
        if (new_capacity > m_capacity)
        {
            T *new_arr = new T[new_capacity];
            for (int i = 0; i < m_size; ++i)
            {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
            m_capacity = new_capacity;
        }
        else
        {
            throw std::length_error("Can't allocate memory of this size");
        }
    }

    template <typename T>
    void Vector<T>::shrink_to_fit()
    {
        if (m_size < m_capacity)
        {
            T *new_arr = new T[m_size];
            for (size_type i = 0; i < m_size; ++i)
            {
                new_arr[i] = std::move(arr[i]);
            }
            delete[] arr;
            arr = new_arr;
            m_capacity = m_size;
        }
    }
    template <typename T>
    typename Vector<T>::iterator Vector<T>::insert(iterator pos, const_reference value)
    {
        size_type index = pos - arr;
        if (m_size >= m_capacity)
        {
            reserve(m_capacity ? m_capacity * 2 : 1);
        }

        for (size_type i = m_size; i > index; --i)
        {
            arr[i] = std::move(arr[i - 1]);
        }
        arr[index] = value;
        ++m_size;
        return arr + index;
    }

    template <typename T>
    void Vector<T>::erase(iterator pos)
    {
        size_type index = pos - arr;
        for (size_type i = index; i < m_size - 1; ++i)
        {
            arr[i] = std::move(arr[i + 1]);
        }
        --m_size;
    }

    template <typename T>
    void Vector<T>::push_back(const_reference value)
    {
        if (m_size >= m_capacity)
        {
            reserve(m_capacity ? m_capacity * 2 : 1);
        }
        arr[m_size] = value;
        ++m_size;
    }

    template <typename T>
    void Vector<T>::pop_back()
    {
        if (m_size > 0)
        {
            --m_size;
        }
        else
        {
            throw std::out_of_range("Vector is empty");
        }
    }

    template <typename T>
    void Vector<T>::swap(Vector &other)
    {
        T *tempArr = arr;
        arr = other.arr;
        other.arr = tempArr;

        size_type tempSize = m_size;
        m_size = other.m_size;
        other.m_size = tempSize;

        size_type tempCapacity = m_capacity;
        m_capacity = other.m_capacity;
        other.m_capacity = tempCapacity;
    }

    template <typename T>
    Vector<T>::Vector(std::initializer_list<value_type> const &items)
    {
        arr = new value_type[items.size()];
        int i = 0;
        for (auto it = items.begin(); it != items.end(); it++)
        {
            arr[i] = *it;
            i++;
        }
        m_size = items.size();
        m_capacity = items.size();
    };

} // namespace s21
