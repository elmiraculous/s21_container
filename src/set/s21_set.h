#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <limits>
namespace s21
{
    template <typename K>
    class Set
    {
    private:
        

    public:
    using key_type = K;
    using value_type = K;
    using reference = K &;
    using const_reference = const K &;
    using size_type = size_t;
    //iterator
    //const_iterator

    Set() : tree_() {}
    Set(std::initializer_list<value_type> const &items) tree_(init) {}




    };


}


#endif
