#include <set>
#include <stdio.h>
int main()
{
    std::set<int> test2 = {52, 54, 45, 48, 53};
    std::set<int>::iterator it = test2.begin();
    for (; it != test2.end(); ++it)
    {
        printf("%d", *it);
        // ASSERT_EQ(*it, *it2);
        // ++it2;
    }
}