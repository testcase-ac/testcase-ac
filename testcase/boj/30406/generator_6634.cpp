#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N = 2*k, k from 1..15 with slight weighting
    int weight = rnd.next(-1, 1);
    int k = rnd.wnext(15, weight) + 1;
    int N = 2 * k;

    // Choose a pattern for diversity
    int pattern = rnd.next(0, 3);
    vector<int> a;
    if (pattern == 0) {
        // Fully random prices in [0,3]
        for (int i = 0; i < N; i++)
            a.push_back(rnd.next(0, 3));
    } else if (pattern == 1) {
        // Cluster around one price
        int c = rnd.next(0, 3);
        for (int i = 0; i < N; i++) {
            if (rnd.next(1, 100) <= 90)
                a.push_back(c);
            else
                a.push_back(rnd.next(0, 3));
        }
    } else if (pattern == 2) {
        // Balanced-ish distribution of all four prices
        int base = N / 4;
        int rem = N - base * 4;
        vector<int> types = {0, 1, 2, 3};
        shuffle(types.begin(), types.end());
        for (int i = 0; i < 4; i++) {
            int cnt = base + (i < rem ? 1 : 0);
            while (cnt--) a.push_back(types[i]);
        }
    } else {
        // Only two distinct prices
        int x = rnd.next(0, 3), y;
        do { y = rnd.next(0, 3); } while (y == x);
        for (int i = 0; i < N; i++)
            a.push_back(rnd.next(0, 1) ? x : y);
    }

    // Shuffle final sequence
    shuffle(a.begin(), a.end());
    // Output
    println(N);
    println(a);
    return 0;
}
