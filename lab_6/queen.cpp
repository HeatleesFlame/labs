#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

vector<int> S(21, 0);
vector<int> R(39, 0);
vector<int> L(41, 0);
vector<int> Q(21, 0);
int n, ch;

void Queen(int j);

int main() {
    cin >> n;         // n <= 20
    for (int i = 1; i <= n; i++) S[i] = 0;
    for (int i = 1 - n; i < n; i++) R[i + 19] = 0;
    for (int i = 2; i <= 2 * n; i++) L[i] = 0;
    ch = 0; 
    Queen(1);
    cout << "var=" << ch << endl;
    return 0;
}

void Queen(int j) {
    for (int i = 1; i <= n; i++) {
        if (S[i] == 0 && R[j - i + 19] == 0 && L[j + i] == 0) {
            S[i] = 1; R[j - i + 19] = 1; L[j + i] = 1; Q[j] = i;
            if (j == n) {
                ch++;
                for (int k = 1; k <= n; k++) { // output permutation
                    cout << Q[k] << setw(3);
                }
                cout << endl;
            } else {
                Queen(j + 1);
            }
            S[i] = 0; R[j - i + 19] = 0; L[j + i] = 0;
        }
    }
}

