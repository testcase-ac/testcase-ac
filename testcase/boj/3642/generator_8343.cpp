#include "testlib.h"
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 5);
    for (int tc = 0; tc < T; tc++) {
        // Generate destination X_dest with one decimal
        int d10;
        if (rnd.next() < 0.3) {
            d10 = rnd.next(10, 1000);      // [1.0,100.0]
        } else {
            d10 = rnd.next(1000, 100000);  // [100.0,10000.0]
        }
        double X_dest = d10 / 10.0;
        int maxPos10 = d10 - 1;  // positions 0.1,0.2,...,X_dest-0.1

        // Generate number of lights L biased low or high
        int weight = rnd.next() < 0.5 ? -2 : 2;
        int L = rnd.wnext(11, weight);  // in [0,10]
        if (L > maxPos10) L = maxPos10;
        if (L < 0) L = 0;

        // Output test case header
        printf("%.1f %d\n", X_dest, L);

        if (L > 0) {
            // Sample L distinct signal positions
            vector<int> pos;
            pos.reserve(maxPos10);
            for (int i = 1; i <= maxPos10; i++) pos.push_back(i);
            shuffle(pos.begin(), pos.end());
            pos.resize(L);
            sort(pos.begin(), pos.end());

            // For each light, generate R and G with one decimal
            for (int i = 0; i < L; i++) {
                double Xi = pos[i] / 10.0;
                int r10 = rnd.next(100, 5000);  // [10.0,500.0]
                double Ri = r10 / 10.0;
                int g10 = rnd.next(100, 5000);
                double Gi = g10 / 10.0;
                printf("%.1f %.1f %.1f\n", Xi, Ri, Gi);
            }
        }
    }
    return 0;
}
