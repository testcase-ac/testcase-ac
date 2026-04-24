#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Union-Find with parity (xor to root)
struct DSU {
    int n;
    vector<int> parent, rnk, parity;
    DSU(int _n): n(_n), parent(n+1), rnk(n+1,0), parity(n+1,0) {
        for(int i = 1; i <= n; i++) parent[i] = i;
    }
    // find root of x, and set parity[x] = xor from x to root
    int find(int x) {
        if(parent[x] == x) return x;
        int p = parent[x];
        int r = find(p);
        parity[x] ^= parity[p];
        return parent[x] = r;
    }
    // get xor from x to its root; call after find(x)
    int getParity(int x) {
        find(x);
        return parity[x];
    }
    // unite x and y with constraint parity_x_y = d (i.e., parity[x] ^ parity[y] == d)
    // return false if contradiction
    bool unite(int x, int y, int d) {
        int rx = find(x);
        int ry = find(y);
        int px = parity[x];
        int py = parity[y];
        if(rx == ry) {
            // must satisfy px ^ py == d
            return ( (px ^ py) == d );
        }
        // attach smaller rank under larger
        if(rnk[rx] < rnk[ry]) {
            parent[rx] = ry;
            // we need parity[rx] ^ px ^ py == d  => parity[rx] = px ^ py ^ d
            parity[rx] = px ^ py ^ d;
        } else {
            parent[ry] = rx;
            // now parity[ry] ^ py ^ px == d  => parity[ry] = px ^ py ^ d
            parity[ry] = px ^ py ^ d;
            if(rnk[rx] == rnk[ry]) rnk[rx]++;
        }
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    // Read N and D
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int D = inf.readInt(0, 200000, "D");
    inf.readEoln();
    
    // Read initial costs G_i and P_i
    for(int i = 1; i <= N; i++) {
        ll Gi = inf.readLong(1LL, 1000000000LL, "G_i");
        inf.readSpace();
        ll Pi = inf.readLong(1LL, 1000000000LL, "P_i");
        inf.readEoln();
    }
    
    // Prepare DSU for constraints
    DSU dsu(N);
    // To check duplicate constraints (unordered pair)
    unordered_set<ll> seen;
    seen.reserve((size_t)D + 200000);
    auto key_pair = [&](int a, int b) {
        if(a > b) swap(a,b);
        // key = a*(N+1) + b fits into ll
        return (ll)a * (N + 1) + b;
    };
    
    // Process initial D designer requests
    for(int idx = 0; idx < D; idx++) {
        int C = inf.readInt(0, 1, "C");
        inf.readSpace();
        int a = inf.readInt(1, N, "i");
        inf.readSpace();
        int b = inf.readInt(1, N, "j");
        inf.readEoln();
        
        ensuref(a != b,
                "Initial constraint %d: endpoints must differ, got (%d, %d)",
                idx, a, b);
        ll key = key_pair(a, b);
        ensuref(seen.insert(key).second,
                "Initial constraint %d: duplicate constraint between %d and %d",
                idx, a, b);
        
        // parity = C (0 = equal, 1 = different)
        if(!dsu.unite(a, b, C)) {
            ensuref(false,
                    "Contradiction after initial constraint %d between %d and %d",
                    idx, a, b);
        }
    }
    
    // Read Q
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();
    
    // Process Q operations
    for(int q = 0; q < Q; q++) {
        int C = inf.readInt(0, 3, "C");
        inf.readSpace();
        int A = inf.readInt(1, N, "A");
        inf.readSpace();
        if(C == 0 || C == 1) {
            int B = inf.readInt(1, N, "B");
            inf.readEoln();
            
            ensuref(A != B,
                    "Query %d: endpoints must differ for C=%d, got (%d, %d)",
                    q, C, A, B);
            ll key = key_pair(A, B);
            ensuref(seen.insert(key).second,
                    "Query %d: duplicate constraint between %d and %d",
                    q, A, B);
            
            // parity = C
            if(!dsu.unite(A, B, C)) {
                ensuref(false,
                        "Contradiction after query %d between %d and %d",
                        q, A, B);
            }
        }
        else if(C == 2) {
            // update G
            ll Bval = inf.readLong(1LL, 1000000000LL, "new_G");
            (void)Bval;
            inf.readEoln();
        }
        else { // C == 3
            // update P
            ll Bval = inf.readLong(1LL, 1000000000LL, "new_P");
            (void)Bval;
            inf.readEoln();
        }
    }
    
    inf.readEof();
    return 0;
}
