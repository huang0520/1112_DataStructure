#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

// Input:  Three current indices of A, B, and C
// Return: The combined indices of the three indices
long long getCombineIndex(const long long &a, const long long &b,
                          const long long &c) {
    return a * 10000000000LL + b * 100000LL + c;
}

// Input:  The combined indices of the three indices
// Return: Three current indices of A, B, and C, where indices[0], indices[1],
// and indices[2] are the index of A, B, and C, respectively.
vector<long long> parseIndex(long long combinedIndex) {
    vector<long long> indices(3);
    indices[2] = combinedIndex % 100000;
    combinedIndex /= 100000;
    indices[1] = combinedIndex % 100000;
    combinedIndex /= 100000;
    indices[0] = combinedIndex;
    return indices;
}

int main() {
    int x, y, z, k;
    cin >> x >> y >> z >> k;
    vector<long long> A(x), B(y), C(z);
    for (int i = 0; i < x; ++i) cin >> A[i];
    for (int i = 0; i < y; ++i) cin >> B[i];
    for (int i = 0; i < z; ++i) cin >> C[i];
    // TODO

    sort(A.begin(), A.end(), greater<long long>());
    sort(B.begin(), B.end(), greater<long long>());
    sort(C.begin(), C.end(), greater<long long>());

    priority_queue<pair<long long, long long>> pq;
    set<long long> record;
    int time = 0;

    pq.emplace(A[0] + B[0] + C[0], getCombineIndex(0, 0, 0));
    record.emplace(getCombineIndex(0, 0, 0));

    while (!pq.empty()) {
        if (time >= k) break;

        auto curr_value = pq.top().first;
        auto curr_index = pq.top().second;
        pq.pop();

        auto split_index = parseIndex(curr_index);

        // cout << split_index[0] << " " << split_index[1] << " " <<
        // split_index[2]
        //      << " " << curr_value << "\n";
        cout << curr_value << "\n";

        vector<long long> next_index(3);
        vector<long long> next_value(3);

        if (split_index[0] + 1 < A.size()) {
            next_index[0] = getCombineIndex(split_index[0] + 1, split_index[1],
                                            split_index[2]);
            next_value[0] =
                A[split_index[0] + 1] + B[split_index[1]] + C[split_index[2]];
        }

        if (split_index[1] + 1 < B.size()) {
            next_index[1] = getCombineIndex(split_index[0], split_index[1] + 1,
                                            split_index[2]);
            next_value[1] =
                A[split_index[0]] + B[split_index[1] + 1] + C[split_index[2]];
        }

        if (split_index[2] + 1 < C.size()) {
            next_index[2] = getCombineIndex(split_index[0], split_index[1],
                                            split_index[2] + 1);
            next_value[2] =
                A[split_index[0]] + B[split_index[1]] + C[split_index[2] + 1];
        }

        for (int i = 0; i < 3; i++)
            if (record.find(next_index[i]) == record.end()) {
                pq.emplace(next_value[i], next_index[i]);
                record.emplace(next_index[i]);
            }

        time++;
    }

    return 0;
}