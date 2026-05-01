#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int A, B, C, M;

    // Bias towards smaller / more readable cases
    int type = rnd.wnext(7, -3); // 0..6, smaller indices more likely

    switch (type) {
        case 0: {
            // Small random values
            A = rnd.next(1, 20);
            B = rnd.next(1, 20);
            C = rnd.next(1, 20);
            M = rnd.next(1, 20);
            break;
        }
        case 1: {
            // A > M => cannot work at all
            M = rnd.next(1, 50);
            A = rnd.next(M + 1, min(M + 10, 1000000));
            B = rnd.next(1, 10000);
            C = rnd.next(1, 10);
            break;
        }
        case 2: {
            // A == M edge
            M = rnd.next(1, 50);
            A = M;
            B = rnd.next(1, 10000);
            C = rnd.next(1, 20);
            break;
        }
        case 3: {
            // Fast recovery: C >= A
            A = rnd.next(1, 100);
            C = rnd.next(A, min(A + 10, 10000));
            M = rnd.next(A, min(A + 50, 1000000));
            B = rnd.next(1, 10000);
            break;
        }
        case 4: {
            // Slow recovery: C < A, moderate M
            A = rnd.next(5, 20);
            C = rnd.next(1, A - 1);
            M = rnd.next(A + 1, min(A + 50, 1000000));
            B = rnd.next(1, 10000);
            break;
        }
        case 5: {
            // Large bounds, potential overflow traps
            A = rnd.next(1, 1000000);
            M = rnd.next(A, 1000000);
            B = rnd.next(1, 10000);
            C = rnd.next(1, 10000);
            break;
        }
        case 6: {
            // Hand-picked corner cases
            vector< array<int,4> > presets = {
                {1, 1, 1, 1},
                {1, 10000, 10000, 1},
                {5, 3, 2, 10},
                {10, 5, 1, 10},
                {11, 5, 1, 10},
                {1000000, 10000, 1, 1000000},
                {1000000, 1, 10000, 1000000}
            };
            auto v = rnd.any(presets);
            A = v[0]; B = v[1]; C = v[2]; M = v[3];
            break;
        }
    }

    println(A, B, C, M);
    return 0;
}
