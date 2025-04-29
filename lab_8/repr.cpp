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


struct Node{
    int data;
    Node* next;
};

Node** read_adj_list(int vertex_num) {
    ifstream fin("output_adj_mat.txt");
    if (!fin.is_open()) {
        cerr << "File not found!";
        return nullptr;
    }


    Node** adj_list = new Node*[vertex_num]();

    for (int i = 0; i < vertex_num; ++i) {
        Node* cur = adj_list[i];
        for (int j = 0; j < vertex_num; ++j) {
            int is_adj;
            fin >> is_adj;
            if (is_adj) {
                Node* newNode = new Node{j, nullptr};
                if (cur == nullptr) {
                    adj_list[i] = newNode;
                } else {
                    cur->next = newNode;
                }
                cur = newNode;
            }
        }
    }
    fin.close();
    return adj_list;
}

void write_adj_list(Node** adj_list, int vertex_num){
    ofstream fout;
    fout.open("output_adj_list.txy");
    for (int i = 0; i < vertex_num; ++i) {
        fout << i << ": ";
        Node* cur = adj_list[i];
        while (cur != nullptr) {
            fout << cur->data << " ";
            cur = cur->next;
        }
        fout << endl;
    }
}

//task 1B
void read_and_write_adj_list(int vertex_num){
    Node** adj_list;
    adj_list = read_adj_list(vertex_num);
    write_adj_list(adj_list, vertex_num);
    return;
}

//task 1C
regex number_pattern("[0-9]+");

int adj_list_to_edge_seq(void){
    ifstream fin;
    fin.open("output_adj_list.txy");
    ofstream fout;
    fout.open("edge_seq.txt");
    string line;
    int last = -1;
    while (!fin.eof()){
        getline(fin, line);
        if (line == "") break;

        auto digits_begin = sregex_iterator(
            line.begin(),
            line.end(),
            number_pattern
        );

        sregex_iterator i = digits_begin;
        auto digits_end = sregex_iterator();
        int vertex = stoi((*i).str());
        ++i;

        while (i != digits_end){
            smatch match = *i;
            string tmp = match.str();
            int digit = stoi(tmp);
            if (digit > last){
                fout<< vertex << " " << digit << endl;
            }
        ++i;
        }
        last = vertex;
    }
    return 0;
}
int main(void){
    int vertex_num = read_and_write_graph_by_edges();
    read_and_write_adj_list(vertex_num);
    adj_list_to_edge_seq();
    return 0;
}