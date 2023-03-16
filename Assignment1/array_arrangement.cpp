#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

int main(void){
    // ios optimization
    ios::sync_with_stdio(false);
    cin.tie(0);

    int case_num;

    //Read input
    cin >> case_num;

    // Each case
    for (int i = 0; i < case_num; i++){
        int arr_size, query_num;
        list <int> arr;
        unordered_map <int, list <int>::iterator> tbl;
        
        cin >> arr_size >> query_num;

        // Create array
        tbl.reserve(arr_size);
        for (int i = 0; i < arr_size; i++){
            arr.push_back(i + 1);
            tbl.emplace(i + 1, prev(arr.end()));
        }
        
        // Query
        for (int i = 0; i < query_num; i++){
            char op;
            int op_val;

            cin >> op >> op_val;

            auto itr = tbl.find(op_val)->second;
            if (op == 'H') arr.splice(arr.begin(), arr, itr);
            else arr.splice(arr.end(), arr, itr);
        }

        // Output
        for (auto i: arr) cout << i << " ";
        cout << "\n";
    }
}