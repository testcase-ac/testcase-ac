#include "testlib.h"
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 20);

    // Hyper-parameter: pattern of the array
    int pattern = rnd.next(0, 3);
    vector<int> A(N);
    if (pattern == 0) {
        // Completely random
        int hi = rnd.next(1, 100);
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(1, hi);
        }
    } else if (pattern == 1) {
        // Ascending order
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(1, 100);
        }
        sort(A.begin(), A.end());
    } else if (pattern == 2) {
        // Descending order
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(1, 100);
        }
        sort(A.begin(), A.end(), greater<int>());
    } else {
        // Few distinct values
        int D = rnd.next(1, max(1, N/2));
        int hi = rnd.next(2, 100);
        vector<int> vals;
        for (int i = 0; i < D; i++) {
            vals.push_back(rnd.next(1, hi));
        }
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        if (vals.empty()) vals.push_back(1);
        for (int i = 0; i < N; i++) {
            A[i] = rnd.any(vals);
        }
    }

    // Hyper-parameter for query length bias
    double smallProb = rnd.next(0.0, 1.0);
    vector<pair<int,int>> qs;
    for (int i = 0; i < M; i++) {
        int s, e;
        if (rnd.next() < smallProb) {
            int maxLen = max(1, N / 3);
            int len = rnd.next(1, maxLen);
            s = rnd.next(1, N - len + 1);
            e = s + len - 1;
        } else {
            s = rnd.next(1, N);
            e = rnd.next(s, N);
        }
        qs.emplace_back(s, e);
    }

    // Output
    println(N, M);
    println(A);
    for (auto &q : qs) {
        println(q.first, q.second);
    }

    return 0;
}
