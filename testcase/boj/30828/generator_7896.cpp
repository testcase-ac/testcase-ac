#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of ingredients
    int N = rnd.next(3, 20);

    // Generate taste values T_i with varied distributions
    vector<int> T(N);
    for (int i = 0; i < N; i++) {
        int typ = rnd.next(1, 3);
        if (typ == 1) {
            // skewed small
            T[i] = rnd.wnext(512, -2);
        } else if (typ == 2) {
            // skewed large
            T[i] = rnd.wnext(512, 2);
        } else {
            // uniform
            T[i] = rnd.next(0, 511);
        }
    }

    // Number of queries
    int Q = rnd.next(5, min(50, N * 3));

    // Build queries with diverse segment lengths
    vector<pair<int,int>> qs;
    // ensure at least one full-range query
    qs.emplace_back(1, N);
    for (int i = 1; i < Q; i++) {
        int mode = rnd.next(1, 3);
        int len;
        if (mode == 1) {
            // small segments
            len = rnd.wnext(N, -1) + 1;
        } else if (mode == 2) {
            // large segments
            len = rnd.wnext(N, 1) + 1;
        } else {
            // uniform segments
            len = rnd.next(1, N);
        }
        int l = rnd.next(1, N - len + 1);
        int r = l + len - 1;
        qs.emplace_back(l, r);
    }
    // Shuffle to randomize query order
    shuffle(qs.begin(), qs.end());

    // Output the test case
    println(N);
    println(T);
    println(Q);
    for (auto &qr : qs) {
        println(qr.first, qr.second);
    }

    return 0;
}
