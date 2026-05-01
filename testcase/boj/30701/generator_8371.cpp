#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of rooms N: bias towards smaller sizes, range [1,20]
    int N = rnd.wnext(20, -1) + 1;
    // Initial power D: small to medium
    int D = rnd.next(1, 50);
    // Number of equipment rooms E: between 0 and min(N,5)
    int E = (N > 0 ? rnd.next(0, min(N, 5)) : 0);
    int M = N - E;

    // Generate unique equipment powers if any
    vector<int> equips;
    if (E > 0) {
        // Ensure a pool large enough to pick E distinct values
        int maxEquip = rnd.next(E + 2, E * 10 + 2);
        vector<int> pool;
        for (int i = 2; i <= maxEquip; ++i) pool.push_back(i);
        shuffle(pool.begin(), pool.end());
        equips.assign(pool.begin(), pool.begin() + E);
        sort(equips.begin(), equips.end());
    }

    // Build rooms
    vector<pair<int,int>> rooms;
    for (int x : equips) {
        rooms.emplace_back(2, x);
    }
    // Monster powers: varied relative to D
    int maxMon = rnd.next(5, max(10, D * 3));
    for (int i = 0; i < M; i++) {
        int x = rnd.next(2, maxMon);
        rooms.emplace_back(1, x);
    }

    // Shuffle room order
    shuffle(rooms.begin(), rooms.end());

    // Output
    println(N, D);
    for (auto &p : rooms) {
        println(p.first, p.second);
    }
    return 0;
}
