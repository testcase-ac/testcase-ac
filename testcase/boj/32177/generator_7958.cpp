#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameters
    int N = rnd.next(6, 12);
    int K = rnd.next(1, 15);
    int T = rnd.next(0, 5);
    // Puang's position and version
    int Xp = rnd.next(-10, 10);
    int Yp = rnd.next(-10, 10);
    int Vp = rnd.next(1, 15);

    // Track used coordinates to ensure uniqueness
    set<pair<int,int>> used;
    used.insert({Xp, Yp});

    struct Friend { int x, y, v, p; };
    vector<Friend> friends;

    // Generate 4 special friends to cover boundary cases
    auto pickCoord = [&](const vector<pair<int,int>>& deltas) {
        for (auto d : deltas) {
            int x = Xp + d.first;
            int y = Yp + d.second;
            if (x >= -20 && x <= 20 && y >= -20 && y <= 20 && !used.count({x,y})) {
                used.insert({x,y});
                return make_pair(x,y);
            }
        }
        // fallback: random free
        for (int it = 0; it < 1000; it++) {
            int x = rnd.next(-20, 20);
            int y = rnd.next(-20, 20);
            if (!used.count({x,y})) {
                used.insert({x,y});
                return make_pair(x,y);
            }
        }
        // should not happen
        return make_pair(0,0);
    };

    // Versions for >T difference
    auto pickHighDiff = [&]() {
        if (Vp + T + 1 <= 15) return Vp + T + 1;
        else return Vp - T - 1;
    };
    // Versions for =T difference
    auto pickEqDiff = [&]() {
        if (Vp + T <= 15) return Vp + T;
        else return Vp - T;
    };

    // Case 1: distance = K, version diff = T
    {
        vector<pair<int,int>> del = {{K,0}, {-K,0}, {0,K}, {0,-K}};
        auto xy = pickCoord(del);
        int vi = pickEqDiff();
        int pi = rnd.next(0,1);
        friends.push_back({xy.first, xy.second, vi, pi});
    }
    // Case 2: distance = K, version diff > T
    {
        vector<pair<int,int>> del = {{K,0}, {-K,0}, {0,K}, {0,-K}};
        auto xy = pickCoord(del);
        int vi = pickHighDiff();
        int pi = rnd.next(0,1);
        friends.push_back({xy.first, xy.second, vi, pi});
    }
    // Case 3: distance = K+1 (>K), version diff <= T
    {
        vector<pair<int,int>> del = {{K+1,0}, {-(K+1),0}, {0,K+1}, {0,-(K+1)}};
        auto xy = pickCoord(del);
        int vi = Vp; // diff 0 <= T
        int pi = rnd.next(0,1);
        friends.push_back({xy.first, xy.second, vi, pi});
    }
    // Case 4: distance = K+1 (>K), version diff > T
    {
        vector<pair<int,int>> del = {{K+1,0}, {-(K+1),0}, {0,K+1}, {0,-(K+1)}};
        auto xy = pickCoord(del);
        int vi = pickHighDiff();
        int pi = rnd.next(0,1);
        friends.push_back({xy.first, xy.second, vi, pi});
    }

    // Remaining random friends
    int rem = N - (int)friends.size();
    // prepare all possible coords in grid
    vector<pair<int,int>> pool;
    for (int x = -20; x <= 20; x++) for (int y = -20; y <= 20; y++) {
        if (!used.count({x,y})) pool.emplace_back(x,y);
    }
    shuffle(pool.begin(), pool.end());
    for (int i = 0; i < rem && i < (int)pool.size(); i++) {
        int x = pool[i].first, y = pool[i].second;
        int v = rnd.next(1, 15);
        int p = rnd.next(0,1);
        friends.push_back({x,y,v,p});
    }

    // Shuffle friend order to randomize indices
    shuffle(friends.begin(), friends.end());

    // Ensure at least one friend has P=1 to avoid trivial zero-output
    bool anyP = false;
    for (auto &f : friends) if (f.p == 1) { anyP = true; break; }
    if (!anyP) friends[ rnd.next(0, N-1) ].p = 1;

    // Output
    println(N, K, T);
    println(Xp, Yp, Vp);
    for (auto &f : friends) {
        println(f.x, f.y, f.v, f.p);
    }

    return 0;
}
