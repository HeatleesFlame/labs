#include <iostream>
#include <cstring>
using namespace std;

int main(void)
{
    char s [20] [10];
    int j = 0;
    while (j < 20)
    {   
        char buffer [10] = {};
        cin.getline(buffer, 10);
        if (buffer[0] == '$')
        {
            break;
        }
        strcpy(s[j],buffer);
        j++;
    }
    for (int i = 1; i < j; i += 2)
    {
        cout << s[i] << endl;
    }
}