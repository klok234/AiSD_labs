#include <iostream>
#include "LinkedList.h"
#include "Sorting.h"

using namespace std;



int main()
{
    cout << "Lab3: Var 10 Task 1,1,0: by Dolzhikov D.A. 6212-100503D\n\n";
    vector<int> a = { 4, 67, 2, 76, 2, 7, 4,7, 1, 7 };
    stats s = quick_sort(a);
    cout << s.comparison_count << " " << s.copy_count << " \n";


    return 0;
}
