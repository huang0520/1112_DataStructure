#include <iostream>
#include <deque>
#include <tuple>

using namespace std;

deque <long> merge_sort(const deque <long>&);

int main(void){
    // ios optimizaion
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    deque <long> array;

    // Read Input
    cin >> n;

    for (auto [i, tmp] = tuple {int{0}, long{0}}; i < n; i++){
        cin >> tmp;
        array.push_back(tmp);
    }

    auto sort = merge_sort(array);

    // Output
    for (auto itr : sort) cout << itr << " ";
    cout << "\n";
}

deque <long> merge_sort(const deque <long> &array){
    if(array.size() == 1) return array;

    deque <long> sorted_left(array.begin(), array.begin() + array.size() / 2);
    deque <long> sorted_right(array.begin() + array.size() / 2, array.end());

    sorted_left = merge_sort(sorted_left);
    sorted_right = merge_sort(sorted_right);

    deque <long> sorted_array;

    while (!sorted_left.empty() && !sorted_right.empty()){
        if (sorted_left.front() > sorted_right.front()){
            sorted_array.push_back(sorted_left.front());
            sorted_left.pop_front();
        }
        else if (sorted_left.front() < sorted_right.front()){
            sorted_array.push_back(sorted_right.front());
            sorted_right.pop_front();
        }
        else {
            sorted_array.push_back(sorted_left.front());
            sorted_array.push_back(sorted_right.front());

            sorted_left.pop_front();
            sorted_right.pop_front();
        }
    }

    if (!sorted_left.empty()){
        for(auto itr : sorted_left){
            sorted_array.push_back(itr);
        }
    }
    else if (!sorted_right.empty()){
        for(auto itr : sorted_right){
            sorted_array.push_back(itr);
        }
    }

    return sorted_array;
}