#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size
    int n = rnd.next(2, 10);
    // Choose distribution type
    int type = rnd.next(0, 4);
    vector<vector<int>> a(n, vector<int>(n));

    // Common hyper-parameters
    int maxVal = rnd.next(10, 200);

    if (type == 0) {
        // Fully random
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = rnd.next(0, maxVal);

    } else if (type == 1) {
        // Diagonal gradient with noise
        int low = rnd.next(0, 50);
        int high = rnd.next(low + 10, 200);
        int delta = rnd.next(0, 10);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double t = (i + j) / (2.0 * (n - 1));
                int v = int(low * (1 - t) + high * t + 0.5) + rnd.next(-delta, delta);
                a[i][j] = max(0, min(200, v));
            }
        }

    } else if (type == 2) {
        // One low-value cluster
        int low = rnd.next(0, 50);
        int high = rnd.next(low + 10, 200);
        int mid = (low + high) / 2;
        int cx = rnd.next(0, n - 1), cy = rnd.next(0, n - 1);
        int r = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int d2 = (i - cx) * (i - cx) + (j - cy) * (j - cy);
                if (d2 <= r * r)
                    a[i][j] = rnd.next(low, mid);
                else
                    a[i][j] = rnd.next(mid, high);
            }
        }

    } else if (type == 3) {
        // Checkerboard of low/high
        int low = rnd.next(0, 50);
        int high = rnd.next(low + 10, 200);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if ((i + j) % 2 == 0)
                    a[i][j] = rnd.next(0, low);
                else
                    a[i][j] = rnd.next(high, 200);
            }
        }

    } else {
        // Only two distinct values
        int v1 = rnd.next(0, 100);
        int v2 = rnd.next(v1 + 1, 200);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = (rnd.next() < 0.5 ? v1 : v2);
    }

    // Output
    println(n);
    for (int i = 0; i < n; i++)
        println(a[i]);

    return 0;
}
