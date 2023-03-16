#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main(void){
    // ios optimization
    ios::sync_with_stdio(false);
    cin.tie(0);

    int case_num;

    //Read input
    cin >> case_num;

    // Each case
    while (case_num--) {
        int arr_size, query_num;

        cin >> arr_size >> query_num;

        list <int> arr;
        vector <list <int>::iterator> tbl;

        // Create arrar
        tbl.reserve(arr_size);
        for (int i = 0; i < arr_size; i++) {
            arr.emplace_back(i + 1);
            tbl.emplace_back(prev(arr.end()));
        }

        // Query
        while (query_num--) {
            char op;
            int op_val;

            cin >> op >> op_val;

            auto itr = tbl[op_val - 1];

            switch (op) {
            case 'H':
                arr.splice(arr.begin(), arr, itr);  
                break;

            case 'T':
                arr.splice(arr.end(), arr, itr);
                break;
            }
        }

        // Output
        for (auto &i: arr) cout << i << " ";
        cout << "\n";
    }
}