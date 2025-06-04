#include <fstream>
#include <iostream>

using namespace std;


void deеp(int k, int target, int* R, int &nom, int &s, int vertex_num, int**mat);

int** init_mat(int n){
    int** A = new int*[n];
    for(int i = 0; i < n; i++) {
        A[i] = new int[n]{}; // init by zero
    }
    return A;
}

void print_mat(int** A, int vertex_num){
    for(int i = 0; i < vertex_num; ++i){
        for(int j = 0; j < vertex_num; ++j){
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

void deep(int k, int target, int &s, int vertex_num, int**mat){
    if (k == target){
        s+=1;
    }
    for (int i = 0;i < vertex_num; ++i){
        if ((mat[k][i]==1)){
            if (i != target){
            }
            deep(i, target, s, vertex_num, mat);
        }
    }
}

int** read_adj_mat(int &vertex_num){
    ifstream fin;
    fin.open("./2_input.txt");

    fin >> vertex_num;

    int **adj_mat;
    adj_mat = init_mat(vertex_num);


    while (!fin.eof()){
        int i, j = 0;
        fin >> i >> j;
        if ((i == -1) || (j == -1)){
            break;
        }
        adj_mat[i][j] = 1;
    }
    fin.close();
    return adj_mat;
}


int count_paths(int** mat, int vertex_num, int start, int target){
    int R[vertex_num]{};
    R[start] = 1;
    int nom = 1;
    int s = 0;
    
    deep(start,target, s, vertex_num, mat);

    return s;
}

int main(){
    int** adj_mat;
    int vertex_num;
    adj_mat = read_adj_mat(vertex_num);
    int s = count_paths(adj_mat, vertex_num, 0, 7);

    cout << s;
}