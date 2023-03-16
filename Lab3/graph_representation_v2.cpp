#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class graph{
public:
    graph(int num_node){
        this->edge_list = vector <vector <int>>(num_node);
    }

    int degree(int u) {return this->edge_list[u].size();}

    char nieghbor(int u, int v){
        auto &i = this->edge_list[u];
        if(find(i.begin(), i.end(), v) != i.end()) return 'Y';
        else return 'N';
    }

    void connect(int u, int v){
        this->edge_list[u].emplace_back(v);
        this->edge_list[v].emplace_back(u);
    }

private:
    vector <vector <int>> edge_list;
};

int main(void){
    // ios optimization
    ios::sync_with_stdio(false);
    cin.tie(0);

    // Read input
    int num_node, num_edge, num_query;
    cin >> num_node >> num_edge >> num_query;

    // Construct the adjency list
    graph G(num_node);

    // Connect the node
    for (int i = 0; i < num_edge; i++){
        int u, v;
        cin >> u >> v;
        G.connect(u, v);
    }

    // Query
    for (int i = 0; i < num_query; i++){
        char op;
        cin >> op;

        if (op == 'D'){
            int val;
            cin >> val;

            cout << G.degree(val) << '\n';
        }
        else if (op == 'N'){
            int u, v;
            cin >> u >> v;

            cout << G.nieghbor(u, v) << '\n';
        }
    }
}