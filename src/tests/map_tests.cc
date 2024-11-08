#include <gtest/gtest.h>

#include <map>

#include "../map/s21_map.h"

using KeyType = int;
using ValueType = std::string;
using MapType = s21::Map<KeyType, ValueType>;

// Фикстура
class MapTest : public ::testing::Test {
 protected:
  MapType map;
  std::map<int, std::string> map2;
};

TEST_F(MapTest, InsertSingleElement) {
  auto result = map.insert({1, "value1"});
  EXPECT_TRUE(result.second);
  EXPECT_EQ(map.at(1), "value1");
}

TEST_F(MapTest, InsertDuplicateElement) {
  map.insert({1, "value1"});
  auto result = map.insert({1, "value2"});
  EXPECT_FALSE(result.second);
  EXPECT_EQ(map.at(1), "value1");
}

TEST_F(MapTest, AccessExistingElement) {
  map.insert({1, "value1"});
  EXPECT_EQ(map.at(1), "value1");
}

TEST_F(MapTest, AccessNonExistingElement) {
  EXPECT_THROW(map.at(999), std::out_of_range);
}

TEST_F(MapTest, OperatorSquareBrackets) {
  map[1] = "value1";
  map2[1] = "value1";
  EXPECT_EQ(map[1], map2[1]);
}

TEST_F(MapTest, EraseElement) {
  map.insert({1, "value1"});
  map.erase(map.begin());
  EXPECT_THROW(map.at(1), std::out_of_range);
}

TEST_F(MapTest, EraseNonExistingElement) {
  map.erase(map.begin());
  EXPECT_TRUE(map.empty());
}

// Тестирование метода clear
TEST_F(MapTest, ClearMap) {
  map.insert({1, "value1"});
  map.insert({2, "value2"});
  map.clear();
  EXPECT_TRUE(map.empty());
}

// Тестирование итераторов
TEST_F(MapTest, IteratorFunctionality) {
  map.insert({1, "value1"});
  map.insert({2, "value2"});
  auto it = map.begin();
  EXPECT_EQ(it->first, 1);
  ++it;
  EXPECT_EQ(it->first, 2);
  ++it;
  EXPECT_EQ(it, map.end());
}

// Тестирование метода insert_many
TEST_F(MapTest, InsertManyElements) {
  map.insert_many(std::make_pair(1, "value1"), std::make_pair(2, "value2"),
                  std::make_pair(3, "value3"));
  EXPECT_EQ(map.at(1), "value1");
  EXPECT_EQ(map.at(2), "value2");
  EXPECT_EQ(map.at(3), "value3");
}

TEST_F(MapTest, InsertEmptyKey) {
  auto result = map.insert({0, "value0"});
  EXPECT_TRUE(result.second);
  EXPECT_EQ(map.at(0), "value0");
}

TEST_F(MapTest, InsertNewValue) {
  auto result2 = map.insert({0, "value3"});
  EXPECT_TRUE(result2.second);
  auto result3 = map.insert_or_assign({0, "value4"});
  EXPECT_FALSE(result3.second);
  EXPECT_EQ(map.at(0), "value4");
}

TEST_F(MapTest, LargeNumberOfElements) {
  for (int i = 0; i < 10000; ++i) {
    map.insert({i, "value" + std::to_string(i)});
  }
  for (int i = 0; i < 10000; ++i) {
    EXPECT_EQ(map.at(i), "value" + std::to_string(i));
  }
}

TEST_F(MapTest, IteratorAfterErase) {
  map.insert({1, "value1"});
  map.insert({2, "value2"});
  auto it = map.begin();
  map.erase(it);
  it = map.begin();
  it++;
  it--;
  EXPECT_EQ(it->first, 2);
}

TEST_F(MapTest, SwapMaps) {
  MapType map2;
  map.insert({1, "value1"});
  map.insert({2, "value2"});
  map2.insert({3, "value3"});
  map2.insert({4, "value4"});
  map.swap(map2);
  EXPECT_EQ(map.at(3), "value3");
  EXPECT_EQ(map.at(4), "value4");
  EXPECT_EQ(map2.at(1), "value1");
  EXPECT_EQ(map2.at(2), "value2");
}

void insert_elements(s21::Map<KeyType, ValueType>& map) {
  map.insert({5, "value5"});
  map.insert({3, "value3"});
  map.insert({7, "value7"});
  map.insert({2, "value2"});
  map.insert({4, "value4"});
  map.insert({6, "value6"});
  map.insert({8, "value8"});
}

TEST_F(MapTest, EraseRootNode) {
  insert_elements(map);

  auto root = map.find(5);

  EXPECT_EQ(root->second, "value5");

  map.erase(root);
  EXPECT_THROW(map.at(5), std::out_of_range);

  EXPECT_EQ(map.at(4), "value4");
  EXPECT_EQ(map.at(6), "value6");
}

TEST_F(MapTest, EraseNodeWithTwoChildren) {
  insert_elements(map);
  map.erase(map.find(3));  // Удаляем узел с двумя детьми
  EXPECT_THROW(map.at(3), std::out_of_range);
  EXPECT_EQ(map.at(2), "value2");
  EXPECT_EQ(map.at(4), "value4");
}

TEST_F(MapTest, EraseNode) {
  insert_elements(map);
  map.erase(map.find(8));
  EXPECT_THROW(map.at(8), std::out_of_range);
  EXPECT_EQ(map.at(7), "value7");
}

TEST_F(MapTest, EraseAllNodes) {
  insert_elements(map);
  map.clear();
  EXPECT_TRUE(map.empty());
}

TEST_F(MapTest, EraseNodeWithoutParent) {
  insert_elements(map);
  map.erase(map.find(2));
  EXPECT_THROW(map.at(2), std::out_of_range);
  EXPECT_EQ(map.at(4), "value4");
}
