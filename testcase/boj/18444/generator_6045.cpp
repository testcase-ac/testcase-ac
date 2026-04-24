#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for skewed selection
    vector<int> tvals = {-3, -1, 1, 3};
    int tV = rnd.any(tvals);
    // Number of villages V: skewed between 1 and 15
    int V = rnd.wnext(15, tV) + 1;
    // Number of post offices P: between 1 and V
    int P = rnd.next(1, V);
    // Cycle length L: skewed between V and V+99
    int tL = rnd.any(tvals);
    ll L = (ll)rnd.wnext(100, tL) + V;
    // Generate cluster centers
    int C = rnd.next(1, min(V, 4));
    vector<ll> centers;
    for (int i = 0; i < C; i++) {
        centers.push_back(rnd.next(0LL, L - 1));
    }
    double clusterProb = rnd.next(0.0, 1.0);
    ll radiusMax = max(1LL, L / 10);
    // Generate village positions
    vector<ll> pos;
    for (int i = 0; i < V; i++) {
        if (rnd.next() < clusterProb) {
            ll c = rnd.any(centers);
            ll delta = rnd.next(-radiusMax, radiusMax);
            ll x = (c + delta) % L;
            if (x < 0) x += L;
            pos.push_back(x);
        } else {
            pos.push_back(rnd.next(0LL, L - 1));
        }
    }
    sort(pos.begin(), pos.end());
    // Output
    println(V, P, L);
    println(pos);
    return 0;
}
