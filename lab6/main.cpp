#include <iostream>
#include <string>
#include "Unordered_Map.h"

using namespace std;


int roman_to_int(const std::string& roman) {

    UnorderedMap<int> roman_map(10);

    roman_map.insert('I', 1);
    roman_map.insert('V', 5);
    roman_map.insert('X', 10);
    roman_map.insert('L', 50);
    roman_map.insert('C', 100);
    roman_map.insert('D', 500);
    roman_map.insert('M', 1000);
    roman_map.print();
    int result = 0;

    for (int i = 0; i < roman.length(); i++)
    {

        Node<int>* iter = roman_map.search(roman[i]);

        if (!iter)
        {
            cout << "Invalid symbol!" << roman[i] << "\n";
            return -1;
        }
        int cur = iter->value;

        if (i + 1 < roman.length())
        {
            iter = roman_map.search(roman[i+1]);
            if (!iter)
            {
                cout << "Invalid symbol!" << roman[i] << "\n";
                return -1;
            }

            int next = iter->value;

            if (cur < next)
            {
                result -= cur;
            }
            else
            {
                result += cur;
            }
        }
        else
        {
            result += cur;
        }
    }
    return result;
}

int main() {
    string roman;
    cout << "Input roman value: ";
    cin >> roman;

    for (char& c : roman)
        c = toupper(c);

    int arabic = roman_to_int(roman);

    if (arabic != -1)
    {
        cout << roman << " in arabic = " << arabic << "\n";
    }

    return 0;
}
