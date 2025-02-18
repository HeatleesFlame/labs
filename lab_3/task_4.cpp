#include <iostream>

using namespace std;

int main(void)
{
    char s [20] [10];
    for (int i = 0; i < 20; i++)
    {
        cin >> s[i];
    }
    for (int i = 0; i < 20; i += 2)
    {
        cout << s[i];
    }
}