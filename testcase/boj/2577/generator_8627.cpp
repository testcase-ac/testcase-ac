#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(1, 6);
    int A, B, C;

    if (mode == 1) {
        // Sample from the statement
        A = 150; B = 266; C = 427;
    } else if (mode == 2) {
        // Minimal boundary-like case
        A = B = C = 100;
    } else if (mode == 3) {
        // Max boundary-like case
        A = B = C = 999;
    } else if (mode == 4) {
        // Product with many zeros (one multiple of 100)
        A = 100 * rnd.next(1, 9); // 100..900
        B = rnd.next(100, 999);
        C = rnd.next(100, 999);
        // Ensure not all factors end with 0 to keep some non-zero digits
        if (B % 10 == 0 && C % 10 == 0) {
            if (C < 999) C += 1;
            else C -= 1;
        }
    } else if (mode == 5) {
        // Search for a triple whose product has many distinct digits
        array<int, 3> bestTriple = {100, 100, 100};
        int bestDistinct = -1;
        int bestLen = -1;

        for (int i = 0; i < 50; i++) {
            int a = rnd.next(100, 999);
            int b = rnd.next(100, 999);
            int c = rnd.next(100, 999);
            long long p = 1LL * a * b * c;
            string s = to_string(p);
            bool vis[10] = {false};
            for (char ch : s) vis[ch - '0'] = true;
            int distinct = 0;
            for (int d = 0; d < 10; d++) if (vis[d]) distinct++;
            int len = (int)s.size();

            if (distinct > bestDistinct || (distinct == bestDistinct && len > bestLen)) {
                bestDistinct = distinct;
                bestLen = len;
                bestTriple = {a, b, c};
            }
        }
        A = bestTriple[0];
        B = bestTriple[1];
        C = bestTriple[2];
    } else {
        // Simple random triple
        A = rnd.next(100, 999);
        B = rnd.next(100, 999);
        C = rnd.next(100, 999);
    }

    println(A);
    println(B);
    println(C);

    return 0;
}
