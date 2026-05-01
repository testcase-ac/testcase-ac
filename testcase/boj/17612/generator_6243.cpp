#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Sample N relatively small for hand-verification, sometimes medium
    int N = rnd.next(1, 30);
    // Sample k both less than N, equal, or greater
    int K = rnd.next(1, max(1, N * 2));
    // Prepare unique IDs
    int idPoolMax = rnd.next(N, N * 10 + 1);
    vector<int> pool(idPoolMax);
    iota(pool.begin(), pool.end(), 1);
    shuffle(pool.begin(), pool.end());
    pool.resize(N);
    // Decide if all weights equal
    bool allEqual = (rnd.next(0, 10) == 0);
    int eqW = allEqual ? rnd.next(1, 20) : 0;
    // Bias for weights: heavy/light clusters
    int bias = 0;
    if (!allEqual && rnd.next(0, 4) == 0) {
        vector<int> opts = {-4, -2, -1, 1, 2, 4};
        bias = rnd.any(opts);
    }
    // Build customers (id, weight)
    vector<pair<int,int>> cust(N);
    for (int i = 0; i < N; i++) {
        int id = pool[i];
        int w = allEqual ? eqW : rnd.wnext(20, bias) + 1;
        cust[i] = {id, w};
    }
    // Decide input ordering mode
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        // random order
        shuffle(cust.begin(), cust.end());
    } else if (mode == 1) {
        // sort by weight asc, then id
        sort(cust.begin(), cust.end(), [](auto &a, auto &b){
            if (a.second != b.second) return a.second < b.second;
            return a.first < b.first;
        });
    } else if (mode == 2) {
        // sort by weight desc, then id
        sort(cust.begin(), cust.end(), [](auto &a, auto &b){
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        });
    } else {
        // group heavy (>= median) then light, preserve relative
        vector<int> ws;
        ws.reserve(N);
        for (auto &p : cust) ws.push_back(p.second);
        sort(ws.begin(), ws.end());
        int med = ws[N/2];
        stable_partition(cust.begin(), cust.end(), [&](auto &p){
            return p.second >= med;
        });
    }
    // Output
    println(N, K);
    for (auto &p : cust) {
        println(p.first, p.second);
    }
    return 0;
}
