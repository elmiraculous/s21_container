#ifndef S21_MAP_H
#define S21_MAP_H

#include <vector>
#include <iostream>

#include "../tree.h"

namespace s21
{

  template <typename K, typename V = K>
  class Map
  {
  public:
    using key_type = K;
    using mapped_type = V;
    using value_type = std::pair<const key_type, mapped_type>;
    using size_type = size_t;
    using iterator = typename Tree<key_type, mapped_type>::iterator;

    Map() : tree_() {}
    Map(std::initializer_list<value_type> init) : tree_(init) {}
    Map(const Map &other) : tree_(other.tree_) {}
    Map(Map &&other) noexcept : tree_(std::move(other.tree_)) {}
    ~Map() = default;

    Map &operator=(const Map &other)
    {
      if (this != &other)
      {
        tree_ = other.tree_;
      }
      return *this;
    }

    Map &operator=(Map &&other) noexcept
    {
      if (this != &other)
      {
        tree_ = std::move(other.tree_);
      }
      return *this;
    }

    mapped_type &at(const key_type &key) { return tree_.at(key); }
    mapped_type &operator[](const key_type &key) { return tree_[key]; }

    bool empty() const noexcept { return tree_.empty(); }
    size_type size() const noexcept { return tree_.size(); }
    size_type max_size() const noexcept { return tree_.max_size(); }

    std::pair<iterator, bool> insert(const value_type &value)
    {
      return tree_.insert(value);
    }

    std::pair<iterator, bool> insert_or_assign(const value_type &value)
    {
      return tree_.insert_or_assign(value);
    }

    void erase(iterator pos) { tree_.erase(pos); }

    void clear() noexcept { tree_.clear(); }

    iterator find(const key_type &key) { return tree_.find_pos(key); }
    bool contains(const key_type &key) const noexcept
    {
      return tree_.contains(key);
    }

    iterator begin() const { return tree_.begin(); }
    iterator end() const { return tree_.end(); }

    void swap(Map &other) { tree_.swap(other.tree_); }

    template <typename... Args>
    std::vector<std::pair<iterator, bool>> insert_many(Args &&...args)
    {
      return tree_.insert_many(std::forward<Args>(args)...);
    }

  private:
    Tree<key_type, mapped_type> tree_;
  };

} // namespace s21

#endif // S21_MAP_H
