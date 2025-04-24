#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>


using namespace std;

const double eps = 1e-12;

void printSolution(double* X, int* L, int n) {
    double* orderedX = new double[n];
    for(int i = 0; i < n; i++) {
        cout << X[i] << " ";
    }
    cout << endl;
}

void buff_push_mat(double** A, int m, int n) {
    ofstream outfile("buff.txt");
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j <= n; ++j) { 
            outfile << A[i][j] << " ";
        }
        outfile << endl;
    }
    outfile.close();
}

double** init_mat(int n, int m){
    double** A = new double*[m];
    for(int i = 0; i < m; i++) {
        A[i] = new double[n + 1];
    }
    return A;
}

void print_mat(double** A, int m, int n){
    for(int i = 0; i < m; ++i){
        for(int j = 0; j <=n; ++j){
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

double** read_mat(int &n, int &m){
    cin >> m;                          
    cin >> n;

    double** A;
    A = init_mat(n, m);

    for(int i = 0; i < m; i++) {
        for(int j = 0; j <= n; j++) {
            cin >> A[i][j];
        }
    }
    return A;
}

void copy_mat(double** dest, double** src, int i, int j, int n){
    for(int k=0;k<n;++k){
        dest[0][k] = src[i][k];
    }
    for(int k=0;k<n;++k){
        dest[1][k] = src[j][k];
    }
}

int triangulate(double** A, int* L,  int m, int n){
    int r = 0;
    for(int i = 0; i < min(m, n); i++) {
        int v = i, u = i;
        for(int j = i; j < m; j++) {
            for(int k = i; k < n; k++) {
                if(fabs(A[j][k]) > fabs(A[v][u])) {
                    v = j;
                    u = k;
                }
            }
        }

        if(fabs(A[v][u]) < eps) {
            r = i;
            break;
        }

        if(v != i) {
            swap(A[i], A[v]);
        }

        if(u != i) {
            for(int k = 0; k < m; k++) {
                swap(A[k][i], A[k][u]);
            }
            swap(L[i], L[u]);
        }

        double div = A[i][i];
        for(int j = i; j <= n; j++) {
            A[i][j] /= div;
        }

        for(int k = 0; k < m; k++) {
            if(k != i) {
                double factor = A[k][i];
                for(int j = i; j <= n; j++) {
                    A[k][j] -= factor * A[i][j];
                }
            }
        }
        r = i + 1;

    }
    return r;
}

int solve(double** A, double* X, int* L, int m, int n, int r){
    bool inconsistent = false;
    for(int i = r; i < m; i++) {
        if(fabs(A[i][n]) > eps) {
            // r(A') == r(A)
            inconsistent = true;
            break;
        }
    }

    if(inconsistent) {
        return 0;
        // cout << "No solutions" << endl;
    }
    else if(r == n) {
        for(int j = 0; j < n; j++) {
            X[L[j]] = A[j][n];
        }
        return 1;
        // cout << "single solution:\n";
        // printSolution(X, L, n);
    }
    else {
        // cout << "Infinity number of solutions" << endl;
        // if (!(input_type=="lines" || input_type=="planes")){
        //     cout << "free variables: ";
        //     for(int j = r; j < n; j++) {
        //         cout << "x" << L[j]+1 << " ";
        //     }
        // }
        // cout << endl;

        for(int j = 0; j < r; j++) {
            X[L[j]] = A[j][n];
            for(int k = r; k < n; k++) {
                X[L[j]] -= A[j][k] * X[L[k]];
            }
        }
        return 2;
        // if (!(input_type=="lines" || input_type=="planes")){
        //     cout << "particular solutions (all free vars = 0)\n";
        //     printSolution(X, L, n);
        // }
    }

}


int main(int argc, char *argv[]){
    int m, n; 
    
    double** A;
    string input_type = argv[1];
    A = read_mat(n, m);
    if (input_type == "lines"){
        buff_push_mat(A, m, n);
        system("python visualization.py");
    }
    
    if (input_type == "area"){
        buff_push_mat(A, m, n);
        system("python visualization.py");
        vector<pair<double, double>> points {};

        for(int i = 0; i < m-1; ++i){
            for(int j=i+1; j <m; ++j){
                double** tmp_mat = init_mat(2, 2);
                int* L = new int[n];
                for(int i = 0; i < n; i++){L[i] = i;}
                double* X = new double[n]{};

                copy_mat(tmp_mat, A, i, j, 3);
                // print_mat(tmp_mat, 2, 2);
                cout << endl;
                int r = triangulate(tmp_mat, L, 2, 2);
                // print_mat(tmp_mat, 2, 2);
                cout << endl;
                int flag = solve(tmp_mat, X, L, 2, 2, r);
                if (flag != 1){
                    cout << "Degenerate behind the screen" << endl;
                    return 0;
                }
                points.push_back(pair(X[0], X[1]));  // noqa
            }
        }
        // S=1/2[(x1-x3)(y2-y3)-(x2-x3)(y2-y3)] 
        double S = 0.5 * fabs((
            (points[1].first - points[0].first)*(points[2].second - points[0].second)
            -(points[2].first - points[0].first)*(points[1].second - points[0].second)
        ));
        cout << S << endl;
        return 0;
    }
    else
    {
        int* L = new int[n];
        double* X = new double[n]{}; 

        for(int i = 0; i < n; i++){L[i] = i;}

        int r = triangulate(A, L, m, n);
        print_mat(A, m, n);
        int flag = solve(A, X, L, m, n, r);
        if (flag == 0){
            cout << "No solutions" << endl;
            return 0;
        }
        if (flag == 1){
            printSolution(X, L, n);
        }
        if (flag == 2 ){
            cout << "Infinity number of solutions" << endl;
        if (!(input_type=="lines" || input_type=="planes")){
            cout << "free variables: ";
            for(int j = r; j < n; j++) {
                cout << "x" << L[j]+1 << " ";
            }
        if (!(input_type=="lines" || input_type=="planes")){
            cout << "particular solutions (all free vars = 0)\n";
            printSolution(X, L, n);
        }
        }
        else

        cout << endl;
        }
        for(int i = 0; i < m; i++) {
            delete[] A[i];
        }
        delete[] A;
        delete[] L;
        delete[] X;
    
        return 0;
    }

    }