#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small dimensions
    int H = rnd.next(1, 10);
    int W = rnd.next(1, 10);
    vector<int> A(W);

    // Choose a pattern for heights
    int pattern = rnd.next(0, 3);
    if (pattern == 0) {
        // Flat
        int h0 = rnd.next(0, H);
        for (int i = 0; i < W; ++i) A[i] = h0;
    } else if (pattern == 1) {
        // Monotonic (increasing or decreasing)
        bool inc = rnd.next(0, 1);
        if (inc) {
            A[0] = rnd.next(0, H);
            for (int i = 1; i < W; ++i)
                A[i] = rnd.next(A[i-1], H);
        } else {
            A[0] = rnd.next(0, H);
            for (int i = 1; i < W; ++i)
                A[i] = rnd.next(0, A[i-1]);
        }
    } else if (pattern == 2 && W >= 3) {
        // Single valley
        int peakL = rnd.next(0, H);
        int peakR = rnd.next(0, H);
        int pos   = rnd.next(1, W - 2);
        int valleyH = rnd.next(0, min(peakL, peakR));
        // Left slope
        for (int i = 0; i <= pos; ++i) {
            if (i == 0) A[i] = peakL;
            else if (i == pos) A[i] = valleyH;
            else A[i] = rnd.next(min(peakL, valleyH), max(peakL, valleyH));
        }
        // Right slope
        for (int i = pos + 1; i < W; ++i) {
            if (i == W - 1) A[i] = peakR;
            else A[i] = rnd.next(min(peakR, valleyH), max(peakR, valleyH));
        }
    } else {
        // Fully random
        for (int i = 0; i < W; ++i)
            A[i] = rnd.next(0, H);
    }

    // Output
    println(H, W);
    println(A);

    return 0;
}
