#include <iostream>
#include <vector>

using namespace std;

int main(void){
    // ios optimization
    ios::sync_with_stdio(false);
    cin.tie(0);

    // Read input
    int num_node, num_edge, num_query;
    cin >> num_node >> num_edge >> num_query;

    // Construct the adjency matrix
    deque <deque <bool>> graph(num_node, deque <bool> (num_node, false));

    // Connect the edge
    for (int i = 0, u, v; i < num_edge; i++){
        cin >> u >> v;
        // Shift u, v left by 1 to align the matrix
        u--;
        v--;
        
        graph[u][v] = true;
        graph[v][u] = true;
    }

    // Query
    for (int i = 0; i < num_query; i++){
        char op;
        cin >> op;
        
        if (op == 'D'){
            int val, count = 0;
            cin >> val;

            // Shift val left by 1 to align matrix
            val--;

            // Count the degree of node
            for (auto i: graph[val])
                if (i == true) count++;
            
            cout << count << '\n';
        }
        else if (op == 'N'){
            int u, v;
            cin >> u >> v;

            // Shift u, v left by 1 to align matrix
            u--;
            v--;

            // Check are two nodes adjent or not
            if (graph[u][v]) cout << "Y\n";
            else cout << "N\n";
        }
    }

    // Print matrix
    // for (auto i: graph){
    //     for (auto j: i) cout << j << ' ';
    //     cout << '\n';
    // }
}