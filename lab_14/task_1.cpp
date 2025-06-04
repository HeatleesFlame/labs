#include <fstream>
#include <iostream>

using namespace std;

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


int** read_adj_mat(int &vertex_num){
    ifstream fin;
    fin.open("./1_input.txt");

    fin >> vertex_num;

    int **adj_mat;
    adj_mat = init_mat(vertex_num);


    while (!fin.eof()){
        int i, j = 0;
        fin >> i >> j;
        if ((i == -1) || (j == -1)){
            break;
        }
        adj_mat[i][j] = adj_mat[j][i] = 1;
    }
    fin.close();
    return adj_mat;
}

int DFS(int** mat, int vertex_num){
    int connectivity[vertex_num]{};
    int q = 0;
    for (int i = 0; i < vertex_num; ++i){
        q++;
        if (connectivity[i] != 0){
            q = connectivity[i];
        }

        connectivity[i] = q;

        for(int j = 0; j < vertex_num; ++j){
            if (mat[i][j] == 1){
                if ((connectivity[j] != 0) != (connectivity[j] == q)){
                    connectivity[i] = connectivity[j];
                    q = connectivity[i];
                    j = 0;
                }
                connectivity[j] = q;
            }
        }
    }
    return q;
}

int main(){
    int** adj_mat;
    int vertex_num;
    adj_mat = read_adj_mat(vertex_num);
    int q = DFS(adj_mat, vertex_num);
    cout << q;
}


