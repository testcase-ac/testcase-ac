#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    printf("%d\n", T);

    for (int tc = 0; tc < T; tc++) {
        // Choose n with some edge-case bias
        int n;
        double r = rnd.next();
        if (r < 0.1) {
            n = 1;
        } else if (r < 0.2) {
            n = 20;
        } else {
            n = rnd.next(2, 15);
        }
        printf("%d\n", n);

        vector<double> ps;
        ps.reserve(n);
        for (int i = 0; i < n; i++) {
            double p;
            int dist = rnd.next(0, 4);
            switch (dist) {
                case 0:
                    p = 0.0;
                    break;
                case 1:
                    p = 1.0;
                    break;
                case 2: {
                    // small probabilities
                    double x = rnd.next();
                    int e = rnd.next(1, 5);
                    p = pow(x, e);
                    break;
                }
                case 3: {
                    // large probabilities
                    double x = rnd.next();
                    int e = rnd.next(1, 5);
                    p = 1.0 - pow(x, e);
                    break;
                }
                default:
                    // uniform
                    p = rnd.next();
                    break;
            }
            // occasional duplicate of a previous value
            if (!ps.empty() && rnd.next() < 0.2) {
                p = ps[rnd.next((int)ps.size())];
            }
            ps.push_back(p);
        }

        // Shuffle to avoid sorted patterns
        shuffle(ps.begin(), ps.end());

        // Output probabilities with six decimals
        for (int i = 0; i < n; i++) {
            printf("%.6f", ps[i]);
            if (i + 1 < n) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
