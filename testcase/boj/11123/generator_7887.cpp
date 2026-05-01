#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: from 1 up to 10
    int T = rnd.next(1, 10);
    println(T);

    for (int tc = 0; tc < T; tc++) {
        // Choose H in one of three regimes: {1}, [2,5], [6,10]
        int regime = rnd.next(0, 2);
        int H;
        if (regime == 0) H = 1;
        else if (regime == 1) H = rnd.next(2, 5);
        else H = rnd.next(6, 10);

        // Similarly for W
        regime = rnd.next(0, 2);
        int W;
        if (regime == 0) W = 1;
        else if (regime == 1) W = rnd.next(2, 5);
        else W = rnd.next(6, 10);

        // Choose density p in low/medium/high regime
        regime = rnd.next(0, 2);
        double p;
        if (regime == 0) {
            // Low density [0, 0.1)
            p = rnd.next() * 0.1;
        } else if (regime == 1) {
            // Medium density [0.2, 0.8)
            p = 0.2 + rnd.next() * 0.6;
        } else {
            // High density [0.9, 1.0)
            p = 0.9 + rnd.next() * 0.1;
        }

        // Output H, W
        println(H, W);

        // Build and print the grid
        for (int i = 0; i < H; i++) {
            string row;
            row.reserve(W);
            for (int j = 0; j < W; j++) {
                // Place '#' with probability p, else '.'
                if (rnd.next() < p) row.push_back('#');
                else row.push_back('.');
            }
            println(row);
        }
    }

    return 0;
}
