#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Length of original string
    int N = rnd.next(1, 30);
    // Total insertions of S, K, H
    int totalIns = rnd.next(0, N * 2);
    int p = rnd.next(0, totalIns);
    int q = rnd.next(0, totalIns - p);
    int r = totalIns - p - q;
    // Modes for structure and distribution
    int mode1 = rnd.next(0, 1);  // 0: fully random, 1: blocky
    int mode2 = rnd.next(0, 3);  // 0: uniform, 1: S-heavy, 2: K-heavy, 3: H-heavy

    string T;
    T.reserve(N);
    // Helper to pick a character by mode2
    auto pickChar = [&]() {
        if (mode2 == 0) {
            return rnd.any(string("SKH"));
        } else if (mode2 == 1) {
            int x = rnd.next(0, 99);
            if (x < 60) return 'S';
            if (x < 85) return 'K';
            return 'H';
        } else if (mode2 == 2) {
            int x = rnd.next(0, 99);
            if (x < 60) return 'K';
            if (x < 85) return 'H';
            return 'S';
        } else {
            int x = rnd.next(0, 99);
            if (x < 60) return 'H';
            if (x < 85) return 'S';
            return 'K';
        }
    };

    if (mode1 == 1) {
        // Blocky pattern
        while ((int)T.size() < N) {
            int blk = rnd.next(1, min(5, N - (int)T.size()));
            char c = pickChar();
            for (int i = 0; i < blk; i++) {
                T.push_back(c);
            }
        }
    } else {
        // Fully random
        for (int i = 0; i < N; i++) {
            T.push_back(pickChar());
        }
    }

    // Output
    println(N, p, q, r);
    println(T);
    return 0;
}
