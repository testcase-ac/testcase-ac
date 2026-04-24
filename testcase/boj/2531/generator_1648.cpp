#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(5, 10);             // number of plates
    int d = rnd.next(5, 20);             // number of sushi types
    int k = rnd.next(2, N);              // window size
    int c = rnd.next(1, d);              // coupon sushi type
    bool include_coupon = rnd.next(0, 1); // whether belt should contain c

    // Decide how many distinct types appear on the belt
    int max_distinct = min(N, d);
    int distinct_cnt = rnd.next(2, max_distinct);

    // Build a set of distinct types for the belt
    vector<int> distinct;
    distinct.reserve(distinct_cnt);
    if (include_coupon) {
        distinct.push_back(c);
    }
    // Pool of other types
    vector<int> pool;
    for (int x = 1; x <= d; x++) {
        if (!include_coupon || x != c)
            pool.push_back(x);
    }
    shuffle(pool.begin(), pool.end());
    int need = distinct_cnt - (int)distinct.size();
    for (int i = 0; i < need; i++) {
        distinct.push_back(pool[i]);
    }

    // Build the belt: ensure each distinct type appears at least once
    vector<int> belt(N);
    int D = distinct.size();
    for (int i = 0; i < D; i++) {
        belt[i] = distinct[i];
    }
    // Fill the rest randomly from distinct types
    for (int i = D; i < N; i++) {
        belt[i] = rnd.any(distinct);
    }
    // Shuffle to randomize positions
    shuffle(belt.begin(), belt.end());

    // Output
    println(N, d, k, c);
    for (int x : belt) {
        println(x);
    }

    return 0;
}
