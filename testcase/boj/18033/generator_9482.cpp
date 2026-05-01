#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 10); // 11 different generation modes
    int n;
    string B;
    int S;

    switch (mode) {
        case 0: {
            // Very small random string
            n = rnd.next(3, 6);
            B.resize(n);
            for (int i = 0; i < n; ++i)
                B[i] = rnd.next(0, 1) ? 'E' : 'P';
            S = rnd.next(1, n - 1);
            break;
        }
        case 1: {
            // All P (no valid slices if all P and any S)
            n = rnd.next(3, 12);
            B.assign(n, 'P');
            S = rnd.next(1, n - 1);
            break;
        }
        case 2: {
            // All E
            n = rnd.next(3, 12);
            B.assign(n, 'E');
            // Often choose S small but sometimes large
            if (rnd.next(0, 1))
                S = 1;
            else if (rnd.next(0, 1))
                S = rnd.next(2, min(4, n - 1));
            else
                S = rnd.next(1, n - 1);
            break;
        }
        case 3: {
            // Alternating pattern
            n = rnd.next(3, 20);
            char start = rnd.next(0, 1) ? 'E' : 'P';
            B.resize(n);
            for (int i = 0; i < n; ++i)
                B[i] = (i % 2 == 0 ? start : (start == 'E' ? 'P' : 'E'));
            // Choose S around 2 or 3 often
            int type = rnd.next(0, 2);
            if (type == 0) S = 2;
            else if (type == 1) S = 3 <= n - 1 ? 3 : 1;
            else S = rnd.next(1, n - 1);
            break;
        }
        case 4: {
            // Exactly one E
            n = rnd.next(3, 20);
            B.assign(n, 'P');
            int pos = rnd.next(0, n - 1);
            B[pos] = 'E';
            if (rnd.next(0, 1))
                S = 1;
            else
                S = rnd.next(1, n - 1);
            break;
        }
        case 5: {
            // Exactly two Es in random distinct positions
            n = rnd.next(4, 20);
            B.assign(n, 'P');
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 2);
            if (b >= a) ++b;
            B[a] = 'E';
            B[b] = 'E';
            // Make S vary: sometimes small, sometimes near n-1
            int t = rnd.next(0, 2);
            if (t == 0) S = rnd.next(1, 3);
            else if (t == 1) S = rnd.next(max(2, n / 2), n - 1);
            else S = rnd.next(1, n - 1);
            break;
        }
        case 6: {
            // E-biased random (many Es)
            n = rnd.next(5, 25);
            B.resize(n);
            for (int i = 0; i < n; ++i)
                B[i] = (rnd.next(0, 4) <= 2 ? 'E' : 'P'); // ~60% E
            S = rnd.next(1, n - 1);
            break;
        }
        case 7: {
            // P-biased random (few Es)
            n = rnd.next(5, 25);
            B.resize(n);
            for (int i = 0; i < n; ++i)
                B[i] = (rnd.next(0, 4) == 0 ? 'E' : 'P'); // ~20% E
            S = rnd.next(1, n - 1);
            break;
        }
        case 8: {
            // Short runs of same character
            n = rnd.next(5, 30);
            B.clear();
            char c = rnd.next(0, 1) ? 'E' : 'P';
            while ((int)B.size() < n) {
                int remaining = n - (int)B.size();
                int runLen = rnd.next(1, min(4, remaining));
                B.append(runLen, c);
                c = (c == 'E' ? 'P' : 'E');
            }
            S = rnd.next(1, n - 1);
            break;
        }
        case 9: {
            // Medium n, mixed S distribution
            n = rnd.next(15, 40);
            B.resize(n);
            for (int i = 0; i < n; ++i)
                B[i] = rnd.next(0, 1) ? 'E' : 'P';
            int t = rnd.next(0, 3);
            if (t == 0) {
                // very small S
                S = rnd.next(1, 3);
            } else if (t == 1) {
                // random S
                S = rnd.next(1, n - 1);
            } else {
                // large S near n-1
                int delta = rnd.next(1, min(5, n - 1));
                S = n - delta;
            }
            break;
        }
        case 10: {
            // Wrap-around critical case: Es at both ends
            n = rnd.next(5, 15);
            B.assign(n, 'P');
            B[0] = 'E';
            B[n - 1] = 'E';
            // Optionally add one more E inside
            if (rnd.next(0, 1)) {
                int pos = rnd.next(1, n - 2);
                B[pos] = 'E';
            }
            // S large enough to allow segments crossing the boundary
            int low = max(2, n / 2);
            S = rnd.next(low, n - 1);
            break;
        }
        default: {
            // Fallback random (should not occur)
            n = 5;
            B = "EPEPE";
            S = 2;
            break;
        }
    }

    println(B);
    println(S);

    return 0;
}
