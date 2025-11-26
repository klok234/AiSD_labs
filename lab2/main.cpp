#include <iostream>
#include "LinkedList.h"

using namespace std;

template <class T>
void reverse(LinkedList<T>& list)
{
    Node<T>* _head = list.get_head();
    if (!_head)
    {
        return;
    }
    Node<T>* iter = _head->next;
    while (iter != _head)
    {
        std::swap(iter->next, iter->prev);
        iter = iter->prev;
    }
    std::swap(_head->next, _head->prev);
    list.set_head(_head->next);
}


int main()
{
    cout << "Lab2: Var 10 Task 2 (base level): by Dolzhikov D.A. 6212-100503D\n\n";

    size_t len = 1;
    cout << "Input length: ";
    cin >> len;
    int start_rand = 0, end_rand = 0;
    unsigned int seed = 0;
    cout << "Input start rand: ";
    cin >> start_rand;
    cout << "Input end rand: ";
    cin >> end_rand;
    cout << "Input seed: ";
    cin >> seed;

    LinkedList<int> list(len, start_rand, end_rand, seed); // tested by 7 1 12 2

    cout << list << "\n";

    list.reverse();
    cout << list << "\n";
    reverse(list);
    cout << list << "\n";

    //list[4] = 0;
    //cout << list[6] << "\n";

    list.push_head(6);
    cout << list << "\n";
    list.pop_head();
    cout << list << "\n";
    list.delete_node(11);
    cout << list << "\n";

    //LinkedList<int> list2 = list;
    //list2[3] = -4;
    //cout << list2 << "\n";

    return 0;
}
