/* generator code */
#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of trees
    int N = rnd.next(3, 10);

    // Starting position
    long long start = rnd.next(1, 10);

    // Decide whether to generate already equal spacing
    bool equal = rnd.next(0, 1);

    vector<long long> pos;
    pos.reserve(N);
    pos.push_back(start);

    if (equal) {
        // Constant gap
        int d = rnd.next(1, 10);
        for (int i = 1; i < N; i++) {
            pos.push_back(pos.back() + d);
        }
    } else {
        // First gap
        int d1 = rnd.next(1, 10);
        pos.push_back(pos.back() + d1);
        // Remaining gaps, ensure at least some variability
        for (int i = 2; i < N; i++) {
            int delta;
            if (i == 2 && rnd.next(0, 1) == 1) {
                // Force a different gap here
                do {
                    delta = rnd.next(1, 10);
                } while (delta == d1);
            } else {
                delta = rnd.next(1, 10);
            }
            pos.push_back(pos.back() + delta);
        }
    }

    // Output
    println(N);
    for (auto x : pos) {
        println(x);
    }
    return 0;
}
