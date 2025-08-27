#include <fstream>
#include <iostream>

using namespace std;

struct edgenode
{
    int y;
    edgenode* next;
};

struct queue
{
    int val;
    queue* next;
};


void insert_edge(edgenode** graph, int v1, int v2){
    edgenode* new_node = new edgenode{};
    new_node -> y = v1;
    new_node -> next = graph[v2];
    graph[v2] = new_node;
}


void deеps(int k, edgenode** S, int* R, int &q ){
    edgenode *p1;
    for (p1=S[k];p1!=NULL;p1=p1->next)
    if (R[p1->y]==0){
        R[p1->y]=q;
        deеps(p1->y, S, R, q);
    }
}

int connectivity(edgenode** graph, int vertex_num, int* R){
    int q = 0;
    for (int i = 0; i < vertex_num; i++){
        if (R[i]==0){
            q++; R[i]=q;
            deеps(i, graph, R, q);
        }
    }
    for (int i = 0; i < vertex_num; ++i){
        cout << i << ": " << R[i] << endl;
    }
    // for (int i = 1; i <= q; ++i){
    //     for (int j = 0; j < vertex_num; ++j){
    //         if (R[j] == i){
    //             cout << j << " " ;
    //         }
    //         else{
    //             cout << endl;
    //         }
            
    //     }
    // }
    return q;   
}

int read_from_file(int* R, int &vertex_num){
    ifstream fin;
    fin.open("2_input.txt");

    fin >> vertex_num;
    edgenode** graph = new edgenode*[vertex_num]{};

    int v1;
    fin >> v1;
    int v2;
    fin>> v2;

    while ((v1 != -1) && (v2 != -1)){
        insert_edge(graph, v1, v2);
        insert_edge(graph, v2, v1);
        fin >> v1;
        fin >> v2;
    }
    R = new int[vertex_num]{};
    return connectivity(graph, vertex_num, R);
}

int main(){
    int* R;
    int q;
    int vertex_num;
    q = read_from_file(R, vertex_num);
    cout << endl;
    cout << q << endl;
    return 0;
}
