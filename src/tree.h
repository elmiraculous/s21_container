#ifndef S21_TREE2_H
#define S21_TREE2_H

#include <iostream>
#include <vector>

namespace s21 {
template <typename K, typename V = K>
class Tree {
 public:
  using key_type = K;
  using mapped_type = V;
  using size_type = size_t;
  using value_type = std::pair<const key_type, mapped_type>;

  Tree() noexcept {};
  explicit Tree(const value_type &elem) noexcept { insert(elem); }
  Tree(std::initializer_list<value_type> const &items);
  Tree(const Tree &other) noexcept { *this = other; };
  Tree(Tree &&other) noexcept { this->swap(other); };
  ~Tree() { clear(); };

  Tree &operator=(const Tree &other) noexcept;
  Tree &operator=(Tree &&other) noexcept;

  bool empty() const noexcept { return !root_; };
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  mapped_type &at(const key_type &key);
  mapped_type &operator[](const key_type &key);

  void clear() noexcept;
  void swap(Tree &other);
  void merge(Tree<K, V> &other);
  bool contains(const key_type &key) const noexcept;

 protected:
  struct Node {
    value_type data_ = value_type{};
    Node *parent_ = nullptr;
    Node *left_ = nullptr;
    Node *right_ = nullptr;

    Node(const value_type &elem) : data_(elem) {}
    ~Node() = default;
  };

  void insert_(Node *&root, const value_type &kv_pair);
  // void contains(key_type &key) const noexcept;
  void clear_node(Node *node);

  void remove_node_with_no_children(Node *cur);
  void remove_node_with_one_child(Node *cur);
  void remove_node_with_two_children(Node *cur);

  class Iterator {
   protected:
    Node *current_;
    const Tree<K, V> *tree_;

   private:
    void move_(bool to_right);
    Node *find_parent_(Node *node);
    Node *find_leftmost_(Node *node);
    Node *find_rightmost_(Node *node);
    Node *max_();
    Node *min_();

   public:
    Iterator(Node *first, const Tree<key_type, mapped_type> &second) noexcept
        : current_(first), tree_(&second) {}
    Iterator(const Iterator &other) {
      current_ = other.current_;
      tree_ = other.tree_;
    }
    ~Iterator() = default;

    bool operator==(const Iterator &other) const {
      return this->current_ == other.current_;
    }
    bool operator!=(const Iterator &other) const {
      return this->current_ != other.current_;
    }

    value_type *operator->() { return &(current_->data_); }
    value_type &operator*() { return current_->data_; }

    Iterator operator++() {
      move_(true);
      return *this;
    };
    Iterator operator++(int);
    Iterator operator--() {
      move_(false);
      return *this;
    };
    Iterator operator--(int);

    Iterator operator=(const Iterator &other) {
      current_ = other.current_;
      return *this;
    }

    Node *Get() { return current_; }
  };

  bool is_multi_set = false;

 public:
  using const_iterator = const Iterator;
  using iterator = Iterator;

  iterator begin() const;
  iterator end() const;
  void erase(iterator pos);
  iterator find_pos(const key_type &key) const noexcept;

  template <class... Args>
  std::vector<std::pair<typename Tree<key_type, mapped_type>::Iterator, bool>>
  insert_many(Args &&...args);

 public:
  std::pair<iterator, bool> insert(const value_type &kv_pair);
  std::pair<iterator, bool> insert_or_assign(const value_type &kv_pair);

 private:
  Node *root_ = nullptr;
  size_type size_ = 0;
  size_type max_size_;
};

template <typename K, typename V>
Tree<K, V>::Tree(const std::initializer_list<value_type> &items) {
  for (auto &item : items) {
    insert(item);
  }
}

template <typename K, typename V>
Tree<K, V> &Tree<K, V>::operator=(const Tree &other) noexcept {
  if (this != &other) {
    for (iterator it = other.begin(); it != other.end(); ++it) {
      this->insert(it);
    }
  }
  return *this;
}

template <typename K, typename V>
Tree<K, V> &Tree<K, V>::operator=(Tree &&other) noexcept {
  if (this != &other) {
    root_ = other.root_;
    this->size_ = other.size_;
    other.clear();
  }
  return *this;
}

template <typename K, typename V>
typename Tree<K, V>::size_type Tree<K, V>::size() const noexcept {
  return size_;
}

template <typename K, typename V>
void Tree<K, V>::clear() noexcept {
  if (root_ != nullptr) {
    clear_node(root_);
  }
  root_ = nullptr;
  size_ = 0;
}

template <typename K, typename V>
inline void Tree<K, V>::swap(Tree &other) {
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
  std::swap(max_size_, other.max_size_);
}

template <typename K, typename V>
inline void Tree<K, V>::remove_node_with_no_children(Node *cur) {
  if (cur->parent_ == nullptr) {
    root_ = nullptr;
  } else {
    if (cur->parent_->left_ == cur) {
      cur->parent_->left_ = nullptr;
    } else {
      cur->parent_->right_ = nullptr;
    }
  }
  delete cur;
  size_--;
}

template <typename K, typename V>
inline void Tree<K, V>::remove_node_with_one_child(Node *cur) {
  Node *child = (cur->left_ != nullptr) ? cur->left_ : cur->right_;

  if (cur->parent_ == nullptr) {
    root_ = child;
  } else {
    if (cur->parent_->left_ == cur) {
      cur->parent_->left_ = child;
    } else {
      cur->parent_->right_ = child;
    }
  }
  child->parent_ = cur->parent_;
  delete cur;
  size_--;
}

template <typename K, typename V>
inline void Tree<K, V>::remove_node_with_two_children(Node *cur) {
  Node *successor = cur->right_;

  while (successor->left_ != nullptr) {
    successor = successor->left_;
  }

  if (successor != cur->right_) {
    if (successor->right_ != nullptr) {
      successor->right_->parent_ = successor->parent_;
    }

    successor->parent_->left_ = successor->right_;
    successor->right_ = cur->right_;
    cur->right_->parent_ = successor;
  }

  successor->left_ = cur->left_;
  if (cur->left_ != nullptr) {
    cur->left_->parent_ = successor;
  }

  successor->parent_ = cur->parent_;
  if (cur->parent_ == nullptr) {
    root_ = successor;
  } else if (cur == cur->parent_->left_) {
    cur->parent_->left_ = successor;
  } else {
    cur->parent_->right_ = successor;
  }

  delete cur;
  size_--;
}

template <typename K, typename V>
inline void Tree<K, V>::erase(iterator pos) {
  Node *cur = pos.Get();
  if (cur == nullptr) {
    return;
  }
  bool cur_left_is_null = (cur->left_ == nullptr);
  bool cur_right_is_null = (cur->right_ == nullptr);

  if (cur_left_is_null && cur_right_is_null) {
    remove_node_with_no_children(cur);
  } else if (cur_left_is_null || cur_right_is_null) {
    remove_node_with_one_child(cur);
  } else {
    remove_node_with_two_children(cur);
  }
}

template <typename K, typename V>
typename Tree<K, V>::size_type Tree<K, V>::max_size() const noexcept {
  return std::numeric_limits<size_t>::max() / sizeof(Tree<K, V>) / 6;
}

template <typename K, typename V>
inline V &Tree<K, V>::at(const key_type &key) {
  if (root_ == nullptr) {
    throw std::out_of_range("Key not found");
  }
  iterator it = find_pos(key);
  if (it != this->end()) {
    return it->second;
  }
  throw std::out_of_range("Key not found");
}

template <typename K, typename V>
inline V &Tree<K, V>::operator[](const key_type &key) {
  if (!contains(key)) {
    std::pair<K, V> elem(key, V());
    insert(elem);
  }
  return at(key);
}

template <typename K, typename V>
void Tree<K, V>::merge(Tree<K, V> &other) {
  if (other.root_ == nullptr || root_ == other.root_) return;
  if (root_ == nullptr) swap(other);

  iterator it_erase = other.begin();

  while (it_erase != other.end) {
    if (!contains(it_erase.first) || is_multi_set) {
      insert(it_erase.second);
      other.erase(it_erase);
    }
    ++it_erase;
  }
}

template <typename K, typename V>
void Tree<K, V>::insert_(Node *&node_, const Tree<K, V>::value_type &kv_pair) {
  Node *current = node_;
  Node *parent = nullptr;

  while (current != nullptr) {
    parent = current;
    if (kv_pair.first <= current->data_.first) {
      current = current->left_;
    } else {
      current = current->right_;
    }
  }

  Node *new_node = new Node(kv_pair);
  new_node->parent_ = parent;

  if (parent == nullptr) {
    node_ = new_node;
  } else if (kv_pair.first <= parent->data_.first) {
    parent->left_ = new_node;
  } else {
    parent->right_ = new_node;
  }
}

template <typename K, typename V>
std::pair<typename Tree<K, V>::iterator, bool> Tree<K, V>::insert(
    const Tree<K, V>::value_type &kv_pair) {
  const K &key = kv_pair.first;

  if ((contains(key) && !is_multi_set)) {
    return {find_pos(key), false};
  }
  if (root_ == nullptr) {
    root_ = new Node(kv_pair);
  } else {
    insert_(root_, kv_pair);
  }
  size_++;
  return {find_pos(key), true};
}

template <typename K, typename V>
std::pair<typename Tree<K, V>::iterator, bool> Tree<K, V>::insert_or_assign(
    const Tree<K, V>::value_type &kv_pair) {
  const K &key = kv_pair.first;
  Iterator it = find_pos(key);
  if (it != end() && !is_multi_set) {
    it->second = kv_pair.second;
    return {it, false};
  }

  if (root_ == nullptr) {
    root_ = new Node(kv_pair);
  } else {
    insert_(root_, kv_pair);
  }

  size_++;
  return {find_pos(key), true};
}

template <typename K, typename V>
inline bool Tree<K, V>::contains(const key_type &key) const noexcept {
  return find_pos(key) != end();
}

template <typename K, typename V>
void Tree<K, V>::clear_node(Node *node) {
  if (node->left_ != nullptr) {
    clear_node(node->left_);
  }
  if (node->right_ != nullptr) {
    clear_node(node->right_);
  }
  delete node;
}

template <typename K, typename V>
typename Tree<K, V>::iterator Tree<K, V>::find_pos(
    const key_type &key) const noexcept {
  Node *current = root_;
  while (current != nullptr) {
    if (key == current->data_.first) {
      return iterator(current, *this);
    } else if (key < current->data_.first) {
      current = current->left_;
    } else {
      current = current->right_;
    }
  }
  return end();
}

template <typename K, typename V>
inline typename Tree<K, V>::iterator Tree<K, V>::begin() const {
  if (this->root_ == nullptr) {
    return iterator(nullptr, *this);
  }
  Node *tmp_node = root_;
  while (tmp_node->left_ != nullptr) {
    tmp_node = tmp_node->left_;
  }
  return iterator(tmp_node, *this);
}

template <typename K, typename V>
inline typename Tree<K, V>::iterator Tree<K, V>::end() const {
  return iterator(nullptr, *this);
}

template <typename K, typename V>
inline typename Tree<K, V>::Iterator Tree<K, V>::Iterator::operator++(int) {
  Iterator tmp(*this);
  move_(true);
  return tmp;
}

template <typename K, typename V>
inline typename Tree<K, V>::Iterator Tree<K, V>::Iterator::operator--(int) {
  Iterator tmp(*this);
  move_(false);
  return tmp;
}

template <typename K, typename V>
inline void Tree<K, V>::Iterator::move_(bool to_right) {
  if (current_ == nullptr) {
    current_ = find_parent_(tree_->begin().Get());
    current_ = to_right ? find_rightmost_(current_) : find_leftmost_(current_);
  } else if ((to_right && current_ == max_()) ||
             (!to_right && current_ == min_())) {
    current_ = nullptr;
  } else {
    Node *next = to_right ? current_->right_ : current_->left_;
    if (next != nullptr) {
      current_ = to_right ? find_leftmost_(next) : find_rightmost_(next);
    } else {
      while (current_->parent_ != nullptr &&
             (to_right
                  ? current_->data_.first > current_->parent_->data_.first
                  : current_->data_.first < current_->parent_->data_.first)) {
        current_ = current_->parent_;
      }
      if (current_->parent_ != nullptr) current_ = current_->parent_;
    }
  }
}

template <typename K, typename V>
inline typename Tree<K, V>::Node *Tree<K, V>::Iterator::find_parent_(
    Node *node) {
  if (node == nullptr) {
    return nullptr;
  }
  while (node->parent_ != nullptr) {
    node = node->parent_;
  }
  return node;
}

template <typename K, typename V>
typename Tree<K, V>::Node *Tree<K, V>::Iterator::find_leftmost_(Node *node) {
  while (node->left_ != nullptr) {
    node = node->left_;
  }
  return node;
}

template <typename K, typename V>
typename Tree<K, V>::Node *Tree<K, V>::Iterator::find_rightmost_(Node *node) {
  while (node->right_ != nullptr) {
    node = node->right_;
  }
  return node;
}

template <typename K, typename V>
inline typename Tree<K, V>::Node *Tree<K, V>::Iterator::max_() {
  Node *tmp_max = find_parent_(current_);
  tmp_max = find_rightmost_(tmp_max);
  return tmp_max;
}

template <typename K, typename V>
inline typename Tree<K, V>::Node *Tree<K, V>::Iterator::min_() {
  Node *tmp_min = find_parent_(current_);
  tmp_min = find_leftmost_(tmp_min);
  return tmp_min;
}

template <typename K, typename V>
template <typename... Args>
std::vector<std::pair<typename Tree<K, V>::iterator, bool>>
Tree<K, V>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> result;
  (result.push_back(insert(std::forward<Args>(args))), ...);
  return result;
}

}  // namespace s21

#endif  // S21_TREE_H_