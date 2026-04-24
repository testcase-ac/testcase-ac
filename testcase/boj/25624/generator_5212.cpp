#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose number of scales N between 2 and 5
    int N = rnd.next(2, 5);

    // Choose sizes S_i for each scale, ensuring total combinations <= 20
    vector<int> S;
    long long prod;
    do {
        S.clear();
        prod = 1;
        for (int i = 0; i < N; i++) {
            int si = rnd.next(1, 3);
            S.push_back(si);
            prod *= si;
        }
    } while (prod > 20);

    // Prepare a shuffled pool of uppercase letters
    vector<char> pool;
    for (char c = 'A'; c <= 'Z'; c++) pool.push_back(c);
    shuffle(pool.begin(), pool.end());

    // Assign disjoint letter sets A_i
    vector<vector<char>> A(N);
    int ptr = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < S[i]; j++) {
            A[i].push_back(pool[ptr++]);
        }
        // sort each A_i to keep internal order simple
        sort(A[i].begin(), A[i].end());
    }

    // Generate all possible result strings (cartesian product)
    vector<string> results;
    string cur;
    function<void(int)> dfs = [&](int pos) {
        if (pos == N) {
            results.push_back(cur);
            return;
        }
        for (char c : A[pos]) {
            cur.push_back(c);
            dfs(pos + 1);
            cur.pop_back();
        }
    };
    dfs(0);

    // Optionally shuffle the list to vary order
    if (rnd.next(0, 1)) {
        shuffle(results.begin(), results.end());
    }

    // Output
    int M = results.size();
    println(N, M);
    for (auto &s : results) {
        println(s);
    }
    return 0;
}
