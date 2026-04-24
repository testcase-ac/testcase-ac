#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small for hand-check
    int T = rnd.next(1, 10);
    println(T);

    // Primitive Pythagorean triples with small values
    vector<array<int,3>> prim = {
        {3, 4, 5},
        {5, 12, 13},
        {8, 15, 17},
        {7, 24, 25},
        {6, 8, 10},
        {9, 12, 15},
        {10, 24, 26}
    };

    for (int i = 0; i < T; i++) {
        bool wantRight = rnd.next(0, 9) < 3; // ~30% chance of right triangle
        int a, b, c;
        if (wantRight) {
            // Generate a right triangle by scaling a primitive triple
            auto t = rnd.any(prim);
            int x = t[0], y = t[1], z = t[2];
            // Keep scale small for readability
            int k = rnd.next(1, 5);
            a = x * k;
            b = y * k;
            c = z * k;
        } else {
            // Generate a non-right but valid triangle
            while (true) {
                a = rnd.next(1, 50);
                b = rnd.next(1, 50);
                int L = abs(a - b) + 1;
                int R = a + b - 1;
                if (L > R) continue;
                c = rnd.next(L, R);
                int ar[3] = {a, b, c};
                sort(ar, ar+3);
                // reject if accidentally right
                if (1LL*ar[0]*ar[0] + 1LL*ar[1]*ar[1] == 1LL*ar[2]*ar[2])
                    continue;
                break;
            }
        }
        // Shuffle sides to avoid ordering clues
        vector<int> sides = {a, b, c};
        shuffle(sides.begin(), sides.end());
        println(sides);
    }

    return 0;
}
