#include <iostream>
#include <cmath>

using namespace std;

int main (void)
{
     double x;
     double y;
     double step;
     cout << "Enter x" << endl;
     cin >> x;
     step = (4 - x)/9;
     for (x; x<=4; x = x + step) {
        y = sin(x)/x;
        cout << "x = " << x << " y= " << y << endl;
     }
     cout << "step= " << step << endl;
    return 0;

}