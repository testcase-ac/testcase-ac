#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a scenario to catch different edge cases
    int scenario = rnd.next(1, 3);
    int N;
    vector<int> v;
    set<int> used;

    if (scenario == 1) {
        // Small N < 5, always missing a full block
        N = rnd.next(1, 4);
        while ((int)v.size() < N) {
            int x = rnd.next(0, 100);
            if (used.insert(x).second)
                v.push_back(x);
        }
    }
    else if (scenario == 2) {
        // Medium N, include a block of length c (0..5) at position S
        N = rnd.next(5, 15);
        int c = rnd.next(0, 5);
        // Start S either very small or fairly large
        int S = (rnd.next(0, 1) == 0 ? rnd.next(0, 1000) : rnd.next(1000000, 100000000));
        // Insert the consecutive block [S, S+c-1]
        for (int i = 0; i < c; i++) {
            used.insert(S + i);
            v.push_back(S + i);
        }
        // Fill rest with numbers far from [S-1, S+c]
        while ((int)v.size() < N) {
            int x = rnd.next(0, 100000000);
            if (used.count(x)) continue;
            if (x < S - 5 || x > S + c + 5) {
                used.insert(x);
                v.push_back(x);
            }
        }
    }
    else {
        // Larger N up to 30, fully random
        N = rnd.next(20, 30);
        while ((int)v.size() < N) {
            int x = rnd.next(0, 1000000000);
            if (used.insert(x).second)
                v.push_back(x);
        }
    }

    // Shuffle so order is random
    shuffle(v.begin(), v.end());

    // Output
    println(N);
    for (int x : v) println(x);

    return 0;
}
