#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <limits>
#include <memory>
#include "../tree.h"
namespace s21
{
    template <typename K>
    class Set
    {
    private:
    public:
        using key_type = K;
        using value_type = key_type;
        using reference = K &;
        using const_reference = const K &;
        using size_type = size_t;
        using iterator = typename Tree<key_type>::iterator;
        using const_iterator = typename Tree<key_type>::const_iterator;
        // iterator
        // const_iterator

        Set() : tree_(){}
        Set(std::initializer_list<key_type> init) {
            std::vector<std::pair<const key_type, key_type>> pair_init;
            for (const auto &key : init) {
                pair_init.push_back(std::make_pair(key, key));
            }
            tree_ = Tree<key_type, key_type>(pair_init);

         }
        Set(const Set &other) : tree_(other.tree_) {}
        Set(Set &&other) noexcept : tree_(std::move(other.tree_)) {}
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
