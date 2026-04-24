#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small N for hand‐checking
    int N = rnd.next(1, 10);

    // Hyper‐parameter: mode of duplicate distribution
    int dupMode = rnd.next(0, 2);
    vector<int> H_line;

    if (dupMode == 0) {
        // All unique heights
        int base = rnd.next(50, 100);
        int cur = base;
        for (int i = 0; i < N; i++) {
            cur += rnd.next(1, 10);
            H_line.push_back(cur);
        }
    }
    else if (dupMode == 1) {
        // All same height
        int h = rnd.next(50, 200);
        H_line.assign(N, h);
    }
    else {
        // Some duplicates, some unique
        int K = rnd.next(1, N);
        vector<int> pool;
        int base = rnd.next(50, 100), cur = base;
        for (int i = 0; i < K; i++) {
            cur += rnd.next(1, 15);
            pool.push_back(cur);
        }
        for (int i = 0; i < N; i++) {
            H_line.push_back(rnd.any(pool));
        }
    }

    // Hyper‐parameter: ordering pattern for the actual lineup
    int orderMode = rnd.next(0, 2);
    if (orderMode == 0) {
        // random order
        shuffle(H_line.begin(), H_line.end());
    } else if (orderMode == 1) {
        // ascending order
        sort(H_line.begin(), H_line.end());
    } else {
        // descending order
        sort(H_line.begin(), H_line.end(), greater<int>());
    }

    // Compute S: for each position, number of previous <= current height
    vector<int> S(N, 0);
    for (int i = 0; i < N; i++) {
        int cnt = 0;
        for (int j = 0; j < i; j++) {
            if (H_line[j] <= H_line[i]) cnt++;
        }
        S[i] = cnt;
    }

    // Shuffle the multiset of heights for input
    vector<int> H_input = H_line;
    shuffle(H_input.begin(), H_input.end());

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(H_input[i]);
    }
    println(S);

    return 0;
}
