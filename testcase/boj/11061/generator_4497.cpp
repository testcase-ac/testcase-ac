#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Choose n, with small chance of trivial
        int n;
        if (rnd.next(0, 9) == 0) {
            n = rnd.next(1, 2);
        } else {
            n = rnd.next(3, 8);
        }
        println(n);
        // Decide weight generation mode
        int mode = rnd.next(0, 2);
        if (n < 3) mode = 0;
        // Parameters
        int maxW = rnd.next(10, 1000);
        // For cluster mode
        int thresh = 0, c = 0;
        vector<int> cid;
        if (mode == 1) {
            // cluster separation threshold
            thresh = rnd.next(1, maxW - 1);
            c = rnd.next(2, n);
            cid.assign(n + 1, 0);
            for (int i = 1; i <= n; i++) {
                cid[i] = rnd.next(0, c - 1);
            }
        }
        // For metric mode
        vector<int> pos(n + 1);
        int noise = 0;
        if (mode == 2) {
            for (int i = 1; i <= n; i++) {
                pos[i] = rnd.next(1, 10);
            }
            noise = rnd.next(0, 2);
        }
        // Output upper triangle
        for (int i = 1; i <= n - 1; i++) {
            vector<int> row;
            row.reserve(n - i);
            for (int j = i + 1; j <= n; j++) {
                int w;
                if (mode == 0) {
                    // uniform random
                    w = rnd.next(1, maxW);
                } else if (mode == 1) {
                    // cluster-based
                    if (cid[i] == cid[j]) {
                        w = rnd.next(1, thresh);
                    } else {
                        w = rnd.next(thresh + 1, maxW);
                    }
                } else {
                    // metric on a line plus small noise
                    w = abs(pos[i] - pos[j]) + 1 + rnd.next(0, noise);
                }
                row.push_back(w);
            }
            println(row);
        }
    }
    return 0;
}
