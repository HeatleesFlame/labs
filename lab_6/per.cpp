#include <iostream>
#include <vector>

void per(int k, int n, std::vector<int>& P, std::vector<int>& R) {
    for (int i = 0; i < n; ++i) {
        if (R[i] == 0) {
            P[k] = i+1;
            R[i] = 1;
            if (k == n - 1) {
                // OUTPUT
                for (int j = 0; j < n; ++j) {
                    std::cout << P[j] << " ";
                }
                std::cout << std::endl;
            } else {
                per(k + 1, n, P, R);
            }
            R[i] = 0;
        }
    }
}

int main(){
    int n = 2;
    std::vector<int> r(n, 0);
    std::vector<int> p{1, 2};
    per(0, n, p, r);
    return 0;
}