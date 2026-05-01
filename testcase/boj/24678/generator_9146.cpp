#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide number of test cases, keeping total output comfortably < 500 chars
    int mode = rnd.next(0, 4);
    int T;
    if (mode == 0) T = 1;
    else if (mode == 1) T = rnd.next(2, 4);
    else if (mode == 2) T = rnd.next(5, 7);
    else if (mode == 3) T = rnd.next(8, 10);
    else T = 12;

    println(T);

    vector<array<long long, 3>> tests;

    // A mix of small, tricky, and large hand-crafted cases
    vector<array<long long, 3>> specials = {
        {1, 1, 1},
        {1, 1, 2},
        {1, 3, 2},      // from example
        {2, 3, 2},      // from example
        {2, 2, 2},
        {1, 2, 3},
        {1, 3, 5},
        {2, 3, 5},
        {3, 3, 3},
        {1000000000, 1000000000, 1000000000},
        {1, 1000000000, 1000000000},
        {1, 2, 1000000000}
    };

    ::shuffle(specials.begin(), specials.end());

    int maxSpecial = min(T, 5); // use at most 5 special cases
    int minSpecial = 1;         // but at least 1
    int useSpecial = rnd.next(minSpecial, maxSpecial);

    for (int i = 0; i < useSpecial; ++i) {
        tests.push_back(specials[i]);
    }

    // Generate the remaining cases with diverse patterns
    while ((int)tests.size() < T) {
        int type = rnd.next(0, 4);
        long long a = 1, b = 1, c = 1;

        if (type == 0) {
            // Very small random values
            a = rnd.next(1, 5);
            b = rnd.next(1, 5);
            c = rnd.next(1, 5);
        } else if (type == 1) {
            // Moderate, near-equal increasing sequence
            a = rnd.next(1, 20);
            b = a + rnd.next(0, 5);
            c = b + rnd.next(0, 5);
        } else if (type == 2) {
            // Large, clustered near 1e9
            const int hi = 1000000000;
            a = hi - rnd.next(0, 20);
            b = hi - rnd.next(0, 20);
            c = hi - rnd.next(0, 20);
        } else if (type == 3) {
            // Highly unbalanced: one huge, two tiny
            long long big = rnd.next(100000000, 1000000000);
            long long small1 = rnd.next(1, 5);
            long long small2 = rnd.next(1, 5);
            a = big;
            b = small1;
            c = small2;
        } else {
            // Fixed sum small configurations, varied distributions
            long long S = rnd.next(3, 60);
            while (true) {
                a = rnd.next(1, (int)S - 2);
                b = rnd.next(1, (int)(S - a - 1));
                c = S - a - b;
                if (c >= 1) break;
            }
        }

        vector<long long> triple = {a, b, c};
        ::shuffle(triple.begin(), triple.end());
        tests.push_back({triple[0], triple[1], triple[2]});
    }

    // Shuffle the order of test cases for additional variability
    ::shuffle(tests.begin(), tests.end());

    for (auto &t : tests) {
        println(t[0], t[1], t[2]);
    }

    return 0;
}
