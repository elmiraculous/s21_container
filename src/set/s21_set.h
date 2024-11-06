#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <limits>
#include "../tree.h"
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
        using iterator = typename Tree<K>::iterator;
        using const_iterator = typename Tree<K>::const_iterator;
        // iterator
        // const_iterator

        Set() : tree_()
        {
        }
        Set(std::initializer_list<value_type> const &items) : tree_(init) {}
        Set(const Set &s) : tree_(s.tree_) {}
        Set(Set &&s) noexcept : tree_(std::move(s.tree_)) {}
        ~Set() = default;

        Set &operator=(const Set &other)
        {
            if (this != &other)
            {
                tree_ = other.tree_;
            }
            return *this;
        }

        Set &operator=(Set &&other) noexcept
        {
            if (this != &other)
            {
                tree_ = std::move(other.tree_);
            }
            return *this;
        }

        bool empty() const noexcept { return tree_.empty(); }
        size_type size() const noexcept { return tree_.size(); }
        size_type max_size() const noexcept { return tree_.max_size(); }

        void clear() noexcept { tree_.clear(); }
        void erase(iterator pos) { tree_.erase(pos); }
        void swap(Set &other) { tree_.swap(other.tree_); }

        std::pair<iterator, bool> insert(const value_type &value)
        {
            return tree_.insert(value);
        }

        iterator begin() const { return tree_.begin(); }
        iterator end() const { return tree_.end(); }

        iterator find(const key_type &key) { return tree_.find_pos(key); }
        bool contains(const key_type &key) const noexcept
        {
            return tree_.contains(key);
        }

    private:
        Tree<key_type> tree_;
    };
}

#endif
