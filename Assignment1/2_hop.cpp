#include <iostream>
#include <vector>

using namespace std;

class graph{
public:
    graph(int size){
        adj_mtx = vector <vector<bool>> (size, vector <bool> (size, 0));
    }

    void link(int, int);
    bool check_two_hop(int, int);
    void display();

private:
    vector <vector <bool>> adj_mtx;
    int size() {return adj_mtx.size();}
};



int main(void){
    // ios optimization
    ios::sync_with_stdio(false);
    cin.tie(0);

    int case_nums;

    // Read input
    cin >> case_nums;

    // Read & opertation;
    for (int i = 0; i < case_nums; i++){
        int vertices_nums, edge_nums, query_nums;

        // Read case info
        cin >> vertices_nums >> edge_nums >> query_nums;

        // Create graph
        graph G(vertices_nums);

        // Link vertices
        for (int i = 0, u, v; i < edge_nums; i++){
            cin >> u >> v;
            G.link(u, v);
        }

        G.display();

        // Query
        for (int i = 0, u, v; i < query_nums; i++){
            cin >> u >> v;
            if (G.check_two_hop(u, v)) cout << "Y\n";
            else cout << "N\n";
        }
    }
}

void graph::link(int u, int v){
    adj_mtx[u - 1][v - 1] = 1;
    adj_mtx[v - 1][u - 1] = 1;
}

bool graph::check_two_hop(int u, int v){
    for (int i = 0; i < size(); i++)
        if (adj_mtx[u - 1][i] && adj_mtx[v - 1][i]) return 1;
    
    return 0;
}

// Show the graph
void graph::display(){
    cout << "==========\n";

    cout << " ";
    for (int i = 0; i < size(); i++) cout << " " << i + 1;
    cout << "\n";

    for (int i = 0; i < size(); i++){
        cout << i + 1;
        for (int j = 0; j < size(); j++) cout << " " << adj_mtx[j][i];
        cout << "\n";
    }
    cout << "==========\n";
}