#include "testlib.h"
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cities
    int N = rnd.next(2, 15);
    // Number of trips, capped for manual checkability
    int maxM = min(20, N * (N - 1) / 2);
    int M = rnd.next(1, maxM);

    // Lane counts w_i
    vector<long long> w(N + 1);
    for (int i = 1; i < N; i++) {
        int p = rnd.next(0, 9);
        if (p < 2) {
            // many edges with 1 lane
            w[i] = 1;
        } else if (p < 4) {
            // some edges with large lanes
            w[i] = rnd.next(1000000LL, 1000000000LL);
        } else {
            // typical small-medium lanes
            w[i] = rnd.next(1, 100);
        }
    }

    // Generate trips (u, v, x)
    vector<tuple<int,int,long long>> trips;
    long long bigMax = 1000000000LL / M;  // to keep sum x_j <= 1e9
    for (int j = 0; j < M; j++) {
        int p = rnd.next(0, 9);
        int u, v;
        if (p < 3) {
            // short trip of length 1
            u = rnd.next(1, N - 1);
            v = u + 1;
        } else if (p < 5) {
            // full-length trip
            u = 1;
            v = N;
        } else {
            // arbitrary trip
            u = rnd.next(1, N - 1);
            v = rnd.next(u + 1, N);
        }
        // cars count with some large values occasionally
        int q = rnd.next(0, 9);
        long long x;
        if (q == 0) {
            x = rnd.next(100000LL, bigMax);
        } else {
            x = rnd.next(1, 1000);
        }
        trips.emplace_back(u, v, x);
    }

    // Output
    println(N, M);
    // lanes
    vector<long long> w_out;
    for (int i = 1; i < N; i++) w_out.push_back(w[i]);
    println(w_out);
    // trips
    for (auto &t : trips) {
        int u, v;
        long long x;
        tie(u, v, x) = t;
        println(u, v, x);
    }
    return 0;
}
