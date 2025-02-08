#include <iostream>

using namespace std;

int main (void)
{
    int sum = 1;
    int fib_1 = 0;
    int fib_2 = 1;
    int fib_new;
    int i = 2;
    int max;
    cin >> max;
    while (sum <= max) 
    {
        fib_new = fib_1 + fib_2;
        fib_1 = fib_2;
        fib_2 = fib_new;
        sum += fib_new;
        i++;
    }
    cout << "i = " << i - 1 << endl;
    cout << "sum = " << sum - fib_new << endl;
    cout << endl;
    return 0;
}