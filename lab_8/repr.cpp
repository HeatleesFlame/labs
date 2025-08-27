#include <iostream>
#include <fstream>
#include <regex>
#include <string>
using namespace std;

double** init_mat(int n){
    double** A = new double*[n];
    for(int i = 0; i < n; i++) {
        A[i] = new double[n]{}; // init by zero
    }
    return A;
}

// 
double** read_adj_mat(int &vertex_num){
    ifstream fin;
    fin.open("./input.txt");

    fin >> vertex_num;

    double **adj_mat;
    adj_mat = init_mat(vertex_num);


    while (!fin.eof()){
        int i, j = 0;
        fin >> i >> j;
        adj_mat[i][j] = adj_mat[j][i] = 1;
    }
    fin.close();
    return adj_mat;
}

void write_adj_mat(double** adj_mat, int vertex_num){
    ofstream fout;
    fout.open("output_adj_mat.txt");
    for(int i=0; i < vertex_num; ++i){
        for(int j=0; j<vertex_num; ++j){
            fout << adj_mat[i][j] << " ";
        }
        fout << endl;
    }
}


// task 1A
int read_and_write_graph_by_edges(){
    int vertex_num;
    double** adj_mat;
    adj_mat = read_adj_mat(vertex_num);
    write_adj_mat(adj_mat, vertex_num);
    return vertex_num;
}


void build_incidence_lists(int vertex_num){
    
    ifstream fin;
    fin.open("./output_adj_mat.txt");
    
    int* vertexes = new int[vertex_num]{};
    int* edges_sublist_len = new int[vertex_num]{};
    int edges_num = 0;
    for (int i = 0; i < vertex_num; ++i){
        int num_incident_edges = 0;
        for(int j = 0; j < vertex_num; ++j){
            int edge_exists;
            fin >> edge_exists;
            if (edge_exists == 1){
                edges_num++;
                num_incident_edges++;
            }
            edges_sublist_len[i] = num_incident_edges;
            if (i > 0){
                vertexes[i] = vertexes[i-1] + edges_sublist_len[i];
            }
        }
    }
    fin.close();
    // debug step 1
    // for(int i = 0; i < vertex_num; ++i){
    //     cout << vertexes[i] << " " << edges_sublist_len[i] << endl;  
    // }
    fin.open("output_adj_mat.txt");
    int* incident_edges = new int[edges_num];
    int k = 0;
    for (int i = 0; i < vertex_num; ++i){
        for (int j = 0; j < vertex_num; ++j){
            int edge_exists;
            fin >> edge_exists;
            if (edge_exists == 1){
                incident_edges[k] = j;
                ++k;
            }
        }
    }
    fin.close();

    ofstream fout;
    fout.open("output_adj_list.txt");
    fout << edges_num << " " << vertex_num << endl;

    for(int i = 0; i < edges_num; ++i){
        fout << incident_edges[i] << " ";
    }
    fout << endl;
    for (int i = 0; i < vertex_num; ++i){
        fout << vertexes[i] << " ";
    }
    fout << endl;
    for (int i = 0; i < vertex_num; ++i){
        fout << edges_sublist_len[i] << " ";
    }
}

int print_edge_seq(void){
    ifstream fin;
    fin.open("output_adj_list.txt");
    int edges;
    fin >> edges;
    int vertexes;
    fin >> vertexes;
    int* D = new int[edges];
    for(int i=0; i<edges; ++i){
        fin >> D[i];
    }
    int* S = new int[vertexes];
    for(int i=0; i<vertexes; ++i){
        fin >> S[i];
    }
    int* L = new int[vertexes];
    for(int i=0; i<vertexes; ++i){
        fin >> L[i];
    }
    fin.close();

    ofstream fout;
    fout.open("output_edges_list.txt");
    for(int i = 0; i < vertexes; ++i){
        for(int j = S[i]; j < S[i]+  L[i]; ++j){
            if (D[j] > i){
                fout << i << " " << D[j] << endl;
            }    
        }
    }

    return 0;
}

int main(void){
    int vertex_num = read_and_write_graph_by_edges();
    build_incidence_lists(vertex_num);
    print_edge_seq();
    return 0;
}