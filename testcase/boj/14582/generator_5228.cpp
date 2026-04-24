#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Decide whether to make a come-from-behind loss (Yes) or not (No)
    bool want_yes = rnd.next(0, 1);
    vector<int> A(9), B(9);

    if (want_yes) {
        // YES case: ensure there is a moment A leads, but final sum A < sum B
        int t = rnd.next(0, 8);  // inning index where A takes lead
        // generate small A, but guarantee A[t] >= 1
        for (int i = 0; i < 9; i++) {
            if (i == t) A[i] = rnd.next(1, 3);
            else A[i] = rnd.next(0, 2);
        }
        int sumA = accumulate(A.begin(), A.end(), 0);
        int sumB = sumA + rnd.next(1, 5);  // ensure B wins
        // zero out B before inning t
        for (int i = 0; i < t; i++) B[i] = 0;
        // distribute remaining runs in B[t..8]
        int rem = sumB;
        for (int i = 0; i < t; i++) rem -= B[i];
        for (int i = t; i < 8; i++) {
            int x = rnd.next(0, rem);
            B[i] = x;
            rem -= x;
        }
        B[8] = rem;
        // we now have a prefix where A leads (after top t), and final B > A
    } else {
        // NO case: ensure A never leads at any point, and B wins
        while (true) {
            for (int i = 0; i < 9; i++) {
                A[i] = rnd.next(0, 3);
                B[i] = rnd.next(0, 3);
            }
            int sumA = accumulate(A.begin(), A.end(), 0);
            int sumB = accumulate(B.begin(), B.end(), 0);
            if (sumB <= sumA) continue;
            bool ok = true;
            int cumA = 0, cumB = 0;
            for (int i = 0; i < 9 && ok; i++) {
                // after top of inning i
                cumA += A[i];
                if (cumA > cumB) { ok = false; break; }
                // after bottom of inning i
                cumB += B[i];
                if (cumA > cumB) { ok = false; break; }
            }
            if (ok) break;
        }
    }

    // Output the test case
    println(A);
    println(B);
    return 0;
}
