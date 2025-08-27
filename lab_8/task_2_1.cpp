// #include <fstream>
// #include <iostream>

// using namespace std;

// struct Node {
//     int
//     int value;
//     Node* next;
// };

// struct Queue {
//     Node* rear;
//     Node* front;
// }

// void init_queue(Queue* q){
//     q -> rear = nullptr;
//     q -> front = nullptr;
// }

// void dequeue(Queue* q){
//     Node* cur = q -> front;

// }

#include <fstream>
#include <iostream>

using namespace std;

struct edgenode
{
    int y;
    edgenode* next;
};




void insert_edge(edgenode** graph, int v1, int v2){
    edgenode* new_node = new edgenode{};
    new_node -> y = v2;
    new_node -> next = graph[v1];
    graph[v1] = new_node;
}


int count_paths(edgenode** graph, int end, int start, int &s){

    if (start == end){
        return 1;
    }
    edgenode* cur = graph[start];
    while (cur != NULL){
        s += count_paths(graph, end, cur -> y, s);
        cur = cur -> next;
    }
    return 0;
}

int read_from_file(){
    ifstream fin;
    fin.open("2_1_input.txt");

    int vertex_num;
    fin >> vertex_num;
    edgenode** graph = new edgenode*[vertex_num]{};

    int v1;
    fin >> v1;
    int v2;
    fin>> v2;

    while ((v1 != -1) && (v2 != -1)){
        insert_edge(graph, v1, v2);
        // insert_edge(graph, v2, v1);
        fin >> v1;
        fin >> v2;
    }
    
    for(int i = 0; i< vertex_num; ++i){
        edgenode* cur = graph[i];
        cout << i << ":";
        while(cur != NULL){
            cout << cur -> y << " ";
            cur = cur -> next;
        }
        cout << endl;
    }
    int s = 0;
    count_paths(graph, 7, 0, s);
    return s;
}

int main(){
    cout << read_from_file();
    return 0;
}