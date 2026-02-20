#include "Set.h"

using namespace std;

bool is_subset(Set& a, Set& b)
{
    vector<int> values_a = a.to_std_vector();
    vector<int> values_b = b.to_std_vector();
    bool result_for_a = true;
    bool result_for_b = true;
    for (auto& i : values_a)
    {
        if (!b.contains(i))
        {
            result_for_a = false;
        }
    }
    for (auto& i : values_b)
    {
        if (!a.contains(i))
        {
            result_for_b = false;
        }
    }
    return result_for_a || result_for_b;
}


int main()
{
    Set s1;
    Set s2;

    for (int i = 0; i < 10; i+=3)
    {
        s1.insert(i);
    }

    for (int i = 0; i < 10; i+=1)
    {
        s2.insert(i);
    }

    s1.print();
    s2.print();

    cout << is_subset(s1, s2) << "\n";

    get_stats_for_set();
    get_stats_for_vector();

    return 0;
}

