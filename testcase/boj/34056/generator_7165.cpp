#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of walls
    int N = rnd.next(2, 12);
    // Initial capacities
    vector<ll> D(N);
    for (int i = 0; i < N; i++) {
        if (rnd.next() < 0.2)
            D[i] = rnd.next(100000000, 1000000000);
        else
            D[i] = rnd.next(1, 20);
    }
    // Number of operations
    int Q = rnd.next(1, N * 3);
    vector<tuple<int,int,ll>> ops;
    int cnt1 = 0, cnt2 = 0;
    auto addOp = [&](int type) {
        if (type == 1) {
            // concert operation
            int c;
            if (rnd.next() < 0.2) {
                // boundary
                c = rnd.any(vector<int>{1, N-1});
            } else {
                c = rnd.next(1, N-1);
            }
            ll x;
            if (rnd.next() < 0.3) {
                x = rnd.next(100000000, 1000000000);
            } else {
                x = rnd.next(1, 50);
            }
            ops.emplace_back(1, c, x);
            cnt1++;
        } else {
            // query operation
            int c = rnd.next(1, N);
            ops.emplace_back(2, c, 0);
            cnt2++;
        }
    };
    if (Q == 1) {
        // Single operation must be a query
        addOp(2);
    } else {
        // Fill first Q-2 ops randomly
        for (int i = 0; i < Q-2; i++) {
            int type = (rnd.next(1, 100) < 40 ? 2 : 1);
            addOp(type);
        }
        // Last two ops: ensure at least one type1 and one type2
        vector<int> lastTypes;
        if (cnt1 == 0) lastTypes.push_back(1);
        if (cnt2 == 0) lastTypes.push_back(2);
        while ((int)lastTypes.size() < 2) lastTypes.push_back(rnd.next(1,2));
        shuffle(lastTypes.begin(), lastTypes.end());
        for (int t : lastTypes) addOp(t);
    }
    // Output
    println(N);
    println(D);
    println(Q);
    for (auto &op : ops) {
        int t = get<0>(op);
        int c = get<1>(op);
        ll x = get<2>(op);
        if (t == 1) println(1, c, x);
        else println(2, c);
    }
    return 0;
}
