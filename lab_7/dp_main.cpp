#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <regex>

using namespace std;

const double eps = 1e-12;

void printSolution(double* X, int* L, int n) {
    double* orderedX = new double[n];
    for(int i = 0; i < n; i++) {
        cout << X[i] << " ";
    }
    cout << endl;
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


//correct input is guaranted
double** read_lines_eqs(int n, int m){
    string line;
    getline(cin, line);
    
    double** A = init_mat(n, m);
    
    int k = 0;
    int i = 0;
    int j = 0;
    string number = "";
    while (i < m && j <= n){
        while (k < line.length()){
            if ((line[k] == 'x' || line[k] == 'y' || line[k] == 'z') && number == ""){
                A[i][j] = 1;
                k++;
                j++;
            }
            while (!(line[k] >= '0' && line[k] <= '9')){
                k++;
            }

            while (line[k]>= '0' && line[k] <= '9')
            {
                number += line[k];
                k++;
            }
            if (number != ""){
            A[i][j] = stoi(number); 
            number = "";
            j++;
            }

            if (line[k] == ','){
                ++i;
                j = 0;
            }
            ++k;
        }
    }
    return A;
}


int main(int argc, char *argv[]){
    int m, n; 
    
    double** A;
    int* L = new int[n];
    double* X = new double[n]{}; 

    for(int i = 0; i < n; i++){L[i] = i;}

    string input_type = argv[1];
    
    if (input_type == "matrix")
    {
        A = read_mat(n, m);
    }
    else if (input_type == "lines")
    {
        n = m = 2;
        A = read_lines_eqs(n, m);
        print_mat(A, m, n);
    }
    else if (input_type == "planes")
    {   
        n = m = 3;
        A = read_lines_eqs(n, m);
    }
    // else if (input_type == "triangle")
    // {
    //     return 0;
    // }


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

    bool inconsistent = false;
    for(int i = r; i < m; i++) {
        if(fabs(A[i][n]) > eps) {
            inconsistent = true;
            break;
        }
    }

    if(inconsistent) {
        cout << "No solutions" << endl;
    }
    else if(r == n) {
        for(int j = 0; j < n; j++) {
            X[L[j]] = A[j][n];
        }
        cout << "single solution:\n";
        printSolution(X, L, n);
    }
    else {
        cout << "Infinity number of solutions" << endl;
        if (!(input_type=="lines" || input_type=="planes")){
            cout << "free variables: ";
            for(int j = r; j < n; j++) {
                cout << "x" << L[j]+1 << " ";
            }
        }
        cout << endl;

        for(int j = 0; j < r; j++) {
            X[L[j]] = A[j][n];
            for(int k = r; k < n; k++) {
                X[L[j]] -= A[j][k] * X[L[k]];
            }
        }
        if (!(input_type=="lines" || input_type=="planes")){
            cout << "particular solutions (all free vars = 0)\n";
            printSolution(X, L, n);
        }
    }

    for(int i = 0; i < m; i++) {
        delete[] A[i];
    }
    delete[] A;
    delete[] L;
    delete[] X;

    return 0;
}