#include <fstream>
#include <iostream>
#include <regex>
#include <string>
using namespace std;

regex number_pattern("[0-9]+");

int main(void){
    ifstream fin;
    fin.open("output_adj_list.txy");
    ofstream fout;
    fout.open("edge_seq.txt");
    string line;
    int last = -1;
    while (!fin.eof()){
        getline(fin, line);
        if (line == "") break;
        auto digits_begin = sregex_iterator(line.begin(), line.end(), number_pattern);
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