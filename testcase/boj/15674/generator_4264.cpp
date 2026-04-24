#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n;
    vector<int> p, r, parity;
    DSU(int _n): n(_n), p(n), r(n,0), parity(n,0) {
        iota(p.begin(), p.end(), 0);
    }
    // find root of x, updating parity[x] to be parity to root
    int find(int x) {
        if (p[x] == x) return x;
        int pr = p[x];
        int root = find(pr);
        parity[x] ^= parity[pr];
        return p[x] = root;
    }
    // get parity of x to its root
    int getParity(int x) {
        find(x);
        return parity[x];
    }
    // can we add constraint x - y = val? (val 0 means equal, 1 means different)
    bool canMerge(int x, int y, int val) {
        int rx = find(x), ry = find(y);
        if (rx == ry) {
            // parity[x] ^ parity[y] must equal val
            return ((parity[x] ^ parity[y]) == val);
        }
        return true;
    }
    // merge with constraint x - y = val
    bool merge(int x, int y, int val) {
        int rx = find(x), ry = find(y);
        int px = parity[x], py = parity[y];
        if (rx == ry) {
            // already consistent?
            return ( (px ^ py) == val );
        }
        // attach smaller rank under larger
        if (r[rx] < r[ry]) {
            // want: px ^ newParity(rx) ^ py = val  => newParity(rx) = px ^ py ^ val
            p[rx] = ry;
            parity[rx] = px ^ py ^ val;
        } else {
            p[ry] = rx;
            parity[ry] = px ^ py ^ val;
            if (r[rx] == r[ry]) r[rx]++;
        }
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of buildings
    int N = rnd.next(1, 10);

    // Initial costs
    vector<pair<int,int>> cost(N);
    for (int i = 0; i < N; i++) {
        cost[i].first  = rnd.next(1, 1000); // G_i
        cost[i].second = rnd.next(1, 1000); // P_i
    }

    // All possible unordered pairs
    int maxPairs = N * (N - 1) / 2;
    int D = rnd.next(0, min(maxPairs, N));

    DSU dsu(N);
    set<pair<int,int>> usedPairs;
    vector<tuple<int,int,int>> initC;

    // Generate D consistent constraints
    while ((int)initC.size() < D && (int)usedPairs.size() < maxPairs) {
        int i = rnd.next(1, N);
        int j = rnd.next(1, N);
        if (i == j) continue;
        int a = min(i, j), b = max(i, j);
        if (usedPairs.count({a,b})) continue;
        int c = rnd.next(0,1);
        if (!dsu.canMerge(i-1, j-1, c)) continue;
        dsu.merge(i-1, j-1, c);
        usedPairs.insert({a,b});
        initC.emplace_back(c, i, j);
    }
    D = initC.size();

    // Generate Q events
    int Q = rnd.next(1, 20);
    vector<tuple<int,int,int>> events;
    for (int qi = 0; qi < Q; qi++) {
        bool doConstraint = false;
        if ((int)usedPairs.size() < maxPairs) {
            doConstraint = (rnd.next(0,1) == 0);
        }
        if (doConstraint) {
            // constraint event
            int i, j, c;
            do {
                i = rnd.next(1, N);
                j = rnd.next(1, N);
                if (i == j) continue;
                int a = min(i,j), b = max(i,j);
                if (usedPairs.count({a,b})) continue;
                c = rnd.next(0,1);
                if (!dsu.canMerge(i-1, j-1, c)) continue;
                break;
            } while (true);
            dsu.merge(i-1, j-1, c);
            int a = min(i,j), b = max(i,j);
            usedPairs.insert({a,b});
            events.emplace_back(c, i, j);
        } else {
            // cost update event
            int tp = rnd.next(2,3);
            int i = rnd.next(1, N);
            int b = rnd.next(1, 1000);
            events.emplace_back(tp, i, b);
        }
    }

    // Output
    println(N, D);
    for (int i = 0; i < N; i++) {
        println(cost[i].first, cost[i].second);
    }
    for (auto &t : initC) {
        int c,i,j;
        tie(c,i,j) = t;
        println(c, i, j);
    }
    println(Q);
    for (auto &t : events) {
        int c,a,b;
        tie(c,a,b) = t;
        println(c, a, b);
    }

    return 0;
}
