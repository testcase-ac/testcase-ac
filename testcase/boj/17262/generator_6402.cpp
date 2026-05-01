#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of fans
    int N = rnd.next(1, 10);
    vector<pair<int,int>> iv;
    if (N == 1) {
        // Single interval edge case
        int s = rnd.next(1, 100);
        int e = rnd.next(s, s + rnd.next(0, 50));
        iv.emplace_back(s, e);
    } else {
        // Choose scenario for diversity
        int scen = rnd.next(1, 4);
        if (scen == 1) {
            // All intervals intersect at a common point T
            int T = rnd.next(1, 100);
            for (int i = 0; i < N; i++) {
                int s = rnd.next(max(1, T - 5), T);
                int e = rnd.next(T, min(100000, T + 5));
                iv.emplace_back(s, e);
            }
        } else if (scen == 2) {
            // All disjoint intervals, sorted by start
            for (int i = 1; i <= N; i++) {
                int base = i * 10 + rnd.next(0,1) * 5;
                int s = base;
                int e = base + rnd.next(0, 4);
                iv.emplace_back(s, e);
            }
        } else if (scen == 3) {
            // Two groups separated by a gap
            int g1 = rnd.next(1, N-1);
            int g2 = N - g1;
            int T1 = rnd.next(1, 100);
            int T2 = T1 + rnd.next(5, 20);
            // group 1 around T1
            for (int i = 0; i < g1; i++) {
                int s = rnd.next(max(1, T1 - 5), T1);
                int e = rnd.next(T1, min(100000, T1 + 5));
                iv.emplace_back(s, e);
            }
            // group 2 around T2
            for (int i = 0; i < g2; i++) {
                int s = rnd.next(max(1, T2 - 5), T2);
                int e = rnd.next(T2, min(100000, T2 + 5));
                iv.emplace_back(s, e);
            }
        } else {
            // Fully random intervals
            for (int i = 0; i < N; i++) {
                int s = rnd.next(1, 100);
                int e = rnd.next(s, min(100000, s + 50));
                iv.emplace_back(s, e);
            }
        }
    }
    // Shuffle order to avoid sorted input
    shuffle(iv.begin(), iv.end());
    // Output
    println(N);
    for (auto &p : iv) {
        println(p.first, p.second);
    }
    return 0;
}
