#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Board width
    int N = rnd.next(1, 30);

    // Choose a scenario for A (domino count) and B (square count)
    int scenario = rnd.next(0, 2);
    int A, B;

    if (scenario == 0) {
        // Low A, force use squares
        A = rnd.next(1, min(5, N));
        int minB = (N - A + 1) / 2;
        if (minB < 1) minB = 1;
        int maxB = min((int)(N / 2), minB + 5);
        if (maxB < minB) maxB = minB;
        B = rnd.next(minB, maxB);
    } else if (scenario == 1) {
        // Low B, force use dominos
        if (N / 2 >= 1) {
            B = rnd.next(1, min(5, N / 2));
        } else {
            B = 1;
        }
        int minA = N - 2 * B;
        if (minA < 1) minA = 1;
        int maxA = min(minA + 5, 30);
        if (maxA < minA) maxA = minA;
        A = rnd.next(minA, maxA);
    } else {
        // Balanced: pick a target c squares, then fit A and B around it
        int maxC = N / 2;
        int c = rnd.next(0, maxC);
        int minB = max(c, 1);
        int maxB = min((int)(N / 2), minB + 5);
        if (maxB < minB) maxB = minB;
        B = rnd.next(minB, maxB);

        int minA = N - 2 * c;
        if (minA < 1) minA = 1;
        int maxA = min(minA + 5, 30);
        if (maxA < minA) maxA = minA;
        A = rnd.next(minA, maxA);
    }

    // Generate beauties
    vector<int> wt = {-1, 0, 1};
    vector<int> D(A), S(B);
    for (int i = 0; i < A; i++) {
        int t = rnd.any(wt);
        D[i] = rnd.wnext(1000000, t) + 1;
    }
    for (int i = 0; i < B; i++) {
        int t = rnd.any(wt);
        S[i] = rnd.wnext(1000000, t) + 1;
    }
    shuffle(D.begin(), D.end());
    shuffle(S.begin(), S.end());

    // Output
    println(N, A, B);
    println(D);
    println(S);

    return 0;
}
