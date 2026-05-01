#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small to medium sizes for manual verification
    int N = rnd.next(1, 15);
    int Q = rnd.next(1, 15);

    // Choose coordinate domain type: 0=small,1=medium,2=extreme
    int domType = rnd.next(0, 2);
    ll xmin, xmax;
    int ext;
    if (domType == 0) {
        xmin = -10; xmax = 10; ext = 5;
    } else if (domType == 1) {
        xmin = -100; xmax = 100; ext = 20;
    } else {
        xmin = -1000000000LL; xmax = 1000000000LL; ext = 0;
    }

    // Generate unique village positions
    vector<ll> xs;
    if (domType < 2) {
        // easy sampling by shuffle
        vector<ll> pool;
        for (ll x = xmin; x <= xmax; ++x) pool.push_back(x);
        shuffle(pool.begin(), pool.end());
        for (int i = 0; i < N; i++) xs.push_back(pool[i]);
    } else {
        // large range, sample with set
        set<ll> sx;
        while ((int)sx.size() < N) {
            ll x = rnd.next(xmin, xmax);
            sx.insert(x);
        }
        xs.assign(sx.begin(), sx.end());
    }
    shuffle(xs.begin(), xs.end());

    // Weight distribution mode: 0=all 1,1=small [1,5],2=full [1,1000]
    int weightMode = rnd.next(0, 2);
    vector<pair<ll,ll>> villages;
    villages.reserve(N);
    for (int i = 0; i < N; i++) {
        ll a;
        if (weightMode == 0) {
            a = 1;
        } else if (weightMode == 1) {
            a = rnd.next(1, 5);
        } else {
            a = rnd.next(1, 1000);
        }
        villages.emplace_back(a, xs[i]);
    }
    shuffle(villages.begin(), villages.end());

    // Generate unique queries
    set<ll> sq;
    while ((int)sq.size() < Q) {
        ll q;
        // sometimes near a village if small/medium domain
        if (domType < 2 && rnd.next(0,1) == 0) {
            ll base = rnd.any(xs);
            q = base + rnd.next(-ext, ext);
        } else {
            q = rnd.next(xmin - ext, xmax + ext);
        }
        sq.insert(q);
    }
    vector<ll> qs(sq.begin(), sq.end());
    shuffle(qs.begin(), qs.end());

    // Output
    println(N, Q);
    for (auto &p : villages) {
        println(p.first, p.second);
    }
    for (ll q : qs) {
        println(q);
    }

    return 0;
}
