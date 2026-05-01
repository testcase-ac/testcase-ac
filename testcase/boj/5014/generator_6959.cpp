#include "testlib.h"
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose building size: small, medium, or large
    int sizeType = rnd.next(0, 2);
    int F;
    if (sizeType == 0) {
        F = rnd.next(10, 50);
    } else if (sizeType == 1) {
        F = rnd.next(100, 500);
    } else {
        F = rnd.next(500000, 1000000);
    }
    // Choose scenario type
    int type = rnd.next(0, 5);
    int S, G, U, D;
    switch (type) {
        case 0:
            // Already at goal
            S = rnd.next(1, F);
            G = S;
            U = rnd.next(0, F);
            D = rnd.next(0, F);
            break;
        case 1:
            // No buttons, S != G
            U = 0; D = 0;
            S = rnd.next(1, F);
            do { G = rnd.next(1, F); } while (G == S);
            break;
        case 2:
            // Up-only reachable
            U = rnd.next(1, F - 1);
            D = 0;
            S = rnd.next(1, F - 1);
            G = rnd.next(S + 1, F);
            break;
        case 3:
            // Down-only reachable
            D = rnd.next(1, F - 1);
            U = 0;
            S = rnd.next(2, F);
            G = rnd.next(1, S - 1);
            break;
        case 4: {
            // Both >0 and reachable via gcd
            U = rnd.next(1, F - 1);
            D = rnd.next(1, F - 1);
            int g = gcd(U, D);
            int maxk = (F - 1) / g;
            int k = rnd.next(1, maxk);
            int diff = k * g;
            if (rnd.next(0, 1)) {
                S = rnd.next(1, F - diff);
                G = S + diff;
            } else {
                S = rnd.next(1 + diff, F);
                G = S - diff;
            }
            break;
        }
        case 5:
            // Both >0 but unreachable by direction-limited
            if (rnd.next(0, 1) == 0) {
                U = rnd.next(1, F - 1);
                D = 0;
                S = rnd.next(2, F);
                G = rnd.next(1, S - 1);
            } else {
                D = rnd.next(1, F - 1);
                U = 0;
                S = rnd.next(1, F - 1);
                G = rnd.next(S + 1, F);
            }
            break;
    }
    println(F, S, G, U, D);
    return 0;
}
