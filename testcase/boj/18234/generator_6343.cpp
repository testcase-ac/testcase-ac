#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of carrot types (small for hand-checkable)
    int N = rnd.next(1, 10);

    // Hyper-parameter: total days T, with variety (small, medium, slightly larger)
    int T;
    int pick = rnd.next(0, 2);
    if (pick == 0) {
        // very small extra days
        T = rnd.next(N, N + 5);
    } else if (pick == 1) {
        // small extra days
        T = rnd.next(N + 6, N + 20);
    } else {
        // up to moderate days
        T = rnd.next(N, N + 100);
    }
    // Ensure T >= N
    T = max(T, N);

    // Generate carrot (w_i, p_i) pairs
    vector<pair<int,int>> carrots;
    carrots.reserve(N);
    for (int i = 0; i < N; i++) {
        int wi = rnd.next(1, 100);
        int rem = 100 - wi;
        int mode;
        if (rem == 0) {
            mode = 0;  // can't grow beyond 100
        } else {
            mode = rnd.next(0, 3);
        }
        int pi;
        if (mode == 0) {
            // no growth
            pi = wi;
        } else if (mode == 1) {
            // small growth by 1..min(5, rem)
            int up = min(5, rem);
            pi = wi + rnd.next(1, up);
        } else if (mode == 2) {
            // medium growth by 6..min(20, rem), fallback to small if rem<6
            if (rem >= 6) {
                int up = min(20, rem);
                pi = wi + rnd.next(6, up);
            } else {
                pi = wi + rnd.next(1, rem);
            }
        } else {
            // large growth: anywhere from wi..100
            pi = rnd.next(wi, 100);
        }
        carrots.emplace_back(wi, pi);
    }

    // Shuffle to avoid any ordering bias
    shuffle(carrots.begin(), carrots.end());

    // Output the generated test case
    println(N, T);
    for (auto &p : carrots) {
        println(p.first, p.second);
    }
    return 0;
}
