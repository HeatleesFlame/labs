#include <iostream>
#include <cmath>

using namespace std;

int main (void)
{
     float x;
     float y;
     float step;
     cout << "Enter x" << endl;
     cin >> x;
     step = (4 - x)/9;
     for (x; x<=4; x = x + step) {
        y = sin(x)/x;
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        cout << endl;
     }
    return 0;

}