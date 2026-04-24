#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of swaps M between 1 and 10
    int M = rnd.next(1, 10);
    // Probability to generate self-swap X == Y
    double selfSwapP = rnd.next(0.0, 1.0);

    vector<pair<int,int>> swaps;
    while ((int)swaps.size() < M) {
        // With some chance, generate a streak of repeated identical swaps
        if (rnd.next() < 0.3 && (int)swaps.size() + 2 <= M) {
            int maxLen = M - swaps.size();
            int L = rnd.next(2, maxLen);
            // choose the swap to repeat
            int x, y;
            if (rnd.next() < selfSwapP) {
                x = rnd.next(1, 3);
                y = x;
            } else {
                x = rnd.next(1, 3);
                do { y = rnd.next(1, 3); } while (y == x);
            }
            for (int i = 0; i < L; i++) {
                swaps.emplace_back(x, y);
            }
        } else {
            int x, y;
            if (rnd.next() < selfSwapP) {
                x = rnd.next(1, 3);
                y = x;
            } else {
                x = rnd.next(1, 3);
                do { y = rnd.next(1, 3); } while (y == x);
            }
            swaps.emplace_back(x, y);
        }
    }

    // Output
    println(M);
    for (auto &p : swaps) {
        println(p.first, p.second);
    }
    return 0;
}
