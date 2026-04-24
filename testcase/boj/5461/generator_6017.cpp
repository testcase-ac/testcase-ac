#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of applicants
    int N = rnd.next(1, 12);
    vector<pair<int,int>> sq(N);
    // Ensure at least one worker can be hired at h=1
    for (int i = 0; i < N; i++) {
        int Q = rnd.next(1, 10);
        int di;
        if (i == 0) {
            di = 1; // first worker always has di=1
        } else {
            di = rnd.next(1, N+2);
        }
        int S;
        if (di <= N) {
            int low = (di - 1) * Q + 1;
            int high = di * Q;
            S = rnd.next(low, high);
        } else {
            // unreachable worker
            int low = Q * (N + 1);
            int high = Q * (N + 2);
            S = rnd.next(low, high);
        }
        sq[i] = {S, Q};
    }
    // Compute feasible costs for each h
    vector<long long> cost(N+1, -1);
    vector<int> possible;
    for (int h = 1; h <= N; h++) {
        vector<int> elig;
        elig.reserve(N);
        for (int i = 0; i < N; i++) {
            int S = sq[i].first, Q = sq[i].second;
            int need = (S + Q - 1) / Q;
            if (need <= h) elig.push_back(Q);
        }
        if ((int)elig.size() >= h) {
            sort(elig.begin(), elig.end());
            long long sumQ = 0;
            for (int i = 0; i < h; i++) sumQ += elig[i];
            cost[h] = sumQ * h;
            possible.push_back(h);
        }
    }
    // Choose a target h and set W exactly to that cost
    int h_target = rnd.any(possible);
    long long W = cost[h_target];
    // Output
    println(N, W);
    for (int i = 0; i < N; i++) {
        println(sq[i].first, sq[i].second);
    }
    return 0;
}
