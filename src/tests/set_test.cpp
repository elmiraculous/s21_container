#include <gtest/gtest.h>

#include <set>

#include "../set/s21_set.h"
using namespace std;

TEST(Set, constructor)
{
    s21::Set<int> test{};
    EXPECT_TRUE(test.empty());
}

TEST(Set, init)
{
    s21::Set<int> test = {52, 54, 45, 48, 53};
    std::set<int> test2 = {52, 54, 45, 48, 53};
    std::set<int>::iterator it = test2.begin();
    s21::Set<int>::iterator it2 = test.begin();
    for (; it != test2.end(); ++it)
    {
        ASSERT_EQ(*it, *it2);
        ++it2;
    }
}

TEST(Set, copy_constructor)
{
    s21::Set<int> test = {52, 54, 45, 48, 53};
    s21::Set<int> test2(test);
    std::set<int> Set = {52, 54, 45, 48, 53};
    std::set<int> Set2(Set);
    std::set<int>::iterator it = Set2.begin();
    s21::Set<int>::iterator it2 = test2.begin();
    for (; it != Set2.end(); ++it)
    {
        ASSERT_EQ(*it, *it2);
        ++it2;
    }
}

TEST(Set, move_constructor)
{
    s21::Set<int> test = {52, 54, 45, 48, 53};
    s21::Set<int> test2(std::move(test));
    std::set<int> Set = {52, 54, 45, 48, 53};
    std::set<int> Set2(std::move(Set));
    std::set<int>::iterator it = Set2.begin();
    s21::Set<int>::iterator it2 = test2.begin();
    for (; it != Set2.end(); ++it)
    {
        ASSERT_EQ(*it, *it2);
        ++it2;
    }
    ASSERT_EQ(test2.size(), Set2.size());
}

TEST(Set, move_assignment)
{
    s21::Set<int> test = {52, 54, 45, 48, 53};
    s21::Set<int> test2 = {7, 4, 8, 0, -1};
    test2 = std::move(test);
    std::set<int> Set = {52, 54, 45, 48, 53};
    std::set<int> Set2 = {7, 4, 8, 0, -1};
    Set2 = std::move(Set);
    std::set<int>::iterator it = Set2.begin();
    s21::Set<int>::iterator it2 = test2.begin();
    for (; it != Set2.end(); ++it)
    {
        ASSERT_EQ(*it, *it2);
        ++it2;
    }
    ASSERT_EQ(test2.size(), Set2.size());
}

TEST(Set, begin)
{
    s21::Set<int> test = {52, 54, 45, 48, 53};
    s21::Set<int>::iterator it = test.begin();
    std::set<int> test2 = {52, 54, 45, 48, 53};
    std::set<int>::iterator it2 = test2.begin();
    ASSERT_EQ(*it, *it2);
    ++it;
    ++it2;
    ASSERT_EQ(*it, *it2);
}

TEST(Set, minus)
{
    s21::Set<int> test = {52, 54, 45, 48, 53};
    s21::Set<int>::iterator it = test.begin();
    std::set<int> test2 = {52, 54, 45, 48, 53};
    std::set<int>::iterator it2 = test2.begin();
    ++it;
    ++it2;
    ASSERT_EQ(*it, *it2);
}

TEST(Set, find)
{
    s21::Set<int> test = {52, 54, 45, 48, 53};
    s21::Set<int>::iterator it = test.find(45);
    std::set<int> test2 = {52, 54, 45, 48, 53};
    std::set<int>::iterator it2 = test2.find(45);
    ASSERT_EQ(*it, *it2);
}

TEST(Set, contains)
{
    s21::Set<int> test = {52, 54, 45, 48, 53};
    bool check = test.contains(60);
    ASSERT_FALSE(check);
}

TEST(Set, insert)
{
    std::set<int> test = {52, 54, 45, 48, 53};
    std::pair<std::set<int>::iterator, bool> check = test.insert(45);
    s21::Set<int> test2 = {52, 54, 45, 48, 53};
    std::pair<s21::Set<int>::iterator, bool> check2 = test2.insert(45);
    ASSERT_EQ(*check.first, *check2.first);
    ASSERT_EQ(check.second, check2.second);
}

TEST(Set, insert2)
{
    std::set<int> test = {52, 54, 45, 48, 53};
    std::pair<std::set<int>::iterator, bool> check = test.insert(0);
    s21::Set<int> test2 = {52, 54, 45, 48, 53};
    std::pair<s21::Set<int>::iterator, bool> check2 = test2.insert(0);
    ASSERT_EQ(*check.first, *check2.first);
    ASSERT_EQ(check.second, check2.second);
}

TEST(Set, clear)
{
    std::set<int> test = {52, 54, 45, 48, 53};
    s21::Set<int> test2 = {52, 54, 45, 48, 53};
    test.clear();
    test2.clear();
    ASSERT_EQ(test.size(), test2.size());
}

TEST(Set, size)
{
    std::set<int> test = {52, 54, 45, 48, 53};
    s21::Set<int> test2 = {52, 54, 45, 48, 53};
    ASSERT_EQ(test.size(), test2.size());
}

TEST(Set, empty)
{
    s21::Set<int> test2{};
    ASSERT_TRUE(test2.empty());
    test2.insert(45);
    ASSERT_FALSE(test2.empty());
}

TEST(Set, swap)
{
    s21::Set<int> test = {52, 54, 45, 48, 53};
    s21::Set<int> test2 = {7, 4, 8, 0, -1, 48, 53};
    std::set<int> Set = {52, 54, 45, 48, 53};
    std::set<int> Set2 = {7, 4, 8, 0, -1, 48, 53};
    test2.swap(test);
    Set2.swap(Set);
    std::set<int>::iterator it = Set2.begin();
    s21::Set<int>::iterator it2 = test2.begin();
    for (; it != Set2.end(); ++it)
    {
        ASSERT_EQ(*it, *it2);
        ++it2;
    }
    it2 = test.begin();
    for (it = Set.begin(); it != Set.end(); ++it)
    {
        ASSERT_EQ(*it, *it2);
        ++it2;
    }
}

TEST(Set, erase)
{
    std::set<int> test = {52, 54, 45, 48, 53};
    s21::Set<int> test2 = {52, 54, 45, 48, 53};
    std::set<int>::iterator it = test.begin();
    s21::Set<int>::iterator it2 = test2.begin();
    ++it;
    ++it2;
    test.erase(it);
    test2.erase(it2);
    it = test.begin();
    it2 = test2.begin();
    for (; it != test.end(); ++it)
    {
        ASSERT_EQ(*it, *it2);
        ++it2;
    }
}

// TEST(Set, InsertMany)
// {
//     s21::Set<int> test;
//     auto results = test.insert_many(52, 54, 45, 48, 53);

//     ASSERT_EQ(static_cast<int>(test.size()), 5);

//     for (const auto &result : results)
//     {
//         ASSERT_TRUE(result.second);
//     }
// }

// TEST(Set, InsertManyDuplicate)
// {
//     s21::Set<int> test = {52, 54, 45};
//     auto results = test.insert_many(52, 54, 45, 48, 53);

//     ASSERT_EQ(static_cast<int>(test.size()), 5);

//     int expected_insertions = 0;
//     for (const auto &result : results)
//     {
//         if (result.second)
//         {
//             ++expected_insertions;
//         }
//     }
//     ASSERT_EQ(expected_insertions, 2);
// }
