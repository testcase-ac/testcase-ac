#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int H, W, R, C, D;
    vector<string> A, B;

    int scenario = rnd.next(0, 6);

    if (scenario == 0) {
        // Very small: 1x1 or short line, mostly straight movement
        int sub = rnd.next(0, 2);
        if (sub == 0) {
            H = 1;
            W = 1;
        } else {
            if (rnd.next(0, 1) == 0) {
                H = 1;
                W = rnd.next(2, 10);
            } else {
                W = 1;
                H = rnd.next(2, 10);
            }
        }
        R = rnd.next(0, H - 1);
        C = rnd.next(0, W - 1);
        D = rnd.next(0, 3);

        A.assign(H, string(W, '0'));
        B.assign(H, string(W, '0'));

        int pattern = rnd.next(0, 2);
        if (pattern == 1) {
            // A random, B all zeros
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    A[i][j] = char('0' + rnd.next(0, 3));
                }
            }
        } else if (pattern == 2) {
            // Both random
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    A[i][j] = char('0' + rnd.next(0, 3));
                    B[i][j] = char('0' + rnd.next(0, 3));
                }
            }
        }
    } else if (scenario == 1) {
        // Corridor (1xN or Nx1) with patterns along the line
        bool horizontal = (rnd.next(0, 1) == 0);
        if (horizontal) {
            H = 1;
            W = rnd.next(3, 15);
        } else {
            W = 1;
            H = rnd.next(3, 15);
        }
        if (horizontal) {
            R = 0;
            C = rnd.next(0, W - 1);
        } else {
            C = 0;
            R = rnd.next(0, H - 1);
        }
        D = rnd.next(0, 3);

        A.assign(H, string(W, '0'));
        B.assign(H, string(W, '0'));

        int kind = rnd.next(0, 2);
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                char d;
                if (kind == 0) {
                    d = '0';
                } else if (kind == 1) {
                    d = char('0' + ((i + j) % 4));
                } else {
                    d = char('0' + rnd.next(0, 3));
                }
                A[i][j] = d;
                if (rnd.next(0, 1) == 0) {
                    B[i][j] = d;
                } else {
                    B[i][j] = char('0' + rnd.next(0, 3));
                }
            }
        }
    } else if (scenario == 2) {
        // Small random grid, biased towards straight motion
        do {
            H = rnd.next(2, 8);
            W = rnd.next(2, 8);
        } while (H * W > 40);

        R = rnd.next(0, H - 1);
        C = rnd.next(0, W - 1);
        D = rnd.next(0, 3);

        A.assign(H, string(W, '0'));
        B.assign(H, string(W, '0'));

        int distType = rnd.next(0, 2);
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                int vA, vB;
                if (distType == 0) {
                    // Mostly zeros, occasional turns
                    vA = (rnd.next(0, 4) == 0) ? rnd.next(0, 3) : 0;
                    vB = (rnd.next(0, 4) == 0) ? rnd.next(0, 3) : 0;
                } else if (distType == 1) {
                    // Same A and B
                    vA = rnd.next(0, 3);
                    vB = vA;
                } else {
                    // Fully random
                    vA = rnd.next(0, 3);
                    vB = rnd.next(0, 3);
                }
                A[i][j] = char('0' + vA);
                B[i][j] = char('0' + vB);
            }
        }
    } else if (scenario == 3) {
        // Medium random grid with various structured patterns
        do {
            H = rnd.next(4, 15);
            W = rnd.next(4, 15);
        } while (H * W < 50 || H * W > 150);

        R = rnd.next(0, H - 1);
        C = rnd.next(0, W - 1);
        D = rnd.next(0, 3);

        A.assign(H, string(W, '0'));
        B.assign(H, string(W, '0'));

        int patternType = rnd.next(0, 3);
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                int a, b;
                if (patternType == 0) {
                    // Checker-like by (i+j)
                    a = (i + j) % 4;
                    if (rnd.next(0, 1) == 0) b = a;
                    else b = rnd.next(0, 3);
                } else if (patternType == 1) {
                    // Vertical stripes
                    a = j % 4;
                    b = (3 - a); // reverse rotation
                } else {
                    // Fully random
                    a = rnd.next(0, 3);
                    b = rnd.next(0, 3);
                }
                A[i][j] = char('0' + a);
                B[i][j] = char('0' + b);
            }
        }
    } else if (scenario == 4) {
        // Symmetric checkerboard A/B to encourage loops
        H = rnd.next(2, 10);
        W = rnd.next(2, 10);
        R = rnd.next(0, H - 1);
        C = rnd.next(0, W - 1);
        D = rnd.next(0, 3);

        A.assign(H, string(W, '0'));
        B.assign(H, string(W, '0'));

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                int parity = (i + j) & 1;
                // Alternate between 90 and 270 degrees
                A[i][j] = char('0' + (parity ? 1 : 3));
                B[i][j] = char('0' + (parity ? 3 : 1));
            }
        }
    } else if (scenario == 5) {
        // Mostly straight, but A==B, medium size
        do {
            H = rnd.next(3, 12);
            W = rnd.next(3, 12);
        } while (H * W > 120);

        R = rnd.next(0, H - 1);
        C = rnd.next(0, W - 1);
        D = rnd.next(0, 3);

        A.assign(H, string(W, '0'));
        B.assign(H, string(W, '0'));

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                int v;
                // 70% chance of 0, 30% random turn
                if (rnd.next(0, 9) < 7) v = 0;
                else v = rnd.next(0, 3);
                A[i][j] = char('0' + v);
                B[i][j] = A[i][j];
            }
        }
    } else {
        // scenario == 6: use one of the sample tests exactly
        int which = rnd.next(0, 1);

        H = 3;
        W = 4;
        R = 1;
        C = 3;
        D = 0;

        A = {
            "1122",
            "1003",
            "3330"
        };
        if (which == 0) {
            // Sample 1
            B = {
                "1200",
                "3031",
                "3332"
            };
        } else {
            // Sample 2
            B = {
                "1200",
                "1031",
                "3332"
            };
        }
    }

    println(H, W);
    println(R, C, D);
    for (int i = 0; i < H; i++) println(A[i]);
    for (int i = 0; i < H; i++) println(B[i]);

    return 0;
}
