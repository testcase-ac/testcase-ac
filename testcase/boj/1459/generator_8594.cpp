#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long X = 0, Y = 0;
    int W = 1, S = 1;

    int type = rnd.next(1, 8);

    switch (type) {
        case 1: {
            // Small random, including possible zeros
            X = rnd.next(0, 20);
            Y = rnd.next(0, 20);
            W = rnd.next(1, 20);
            S = rnd.next(1, 20);
            break;
        }
        case 2: {
            // Large coordinates, S >= 2W (no-diagonal optimal zone)
            W = rnd.next(1, 5000);
            long long maxMult = min(10000LL / W, 10LL);
            int mult = rnd.next(2, (int)maxMult);
            S = W * mult;
            X = rnd.next(0, 1000000000);
            Y = rnd.next(0, 1000000000);
            break;
        }
        case 3: {
            // Moderate coordinates, W <= S <= 2W (mixed movement zone)
            W = rnd.next(1, 10000);
            long long ub = min(2LL * W, 10000LL);
            S = rnd.next(W, (int)ub);
            X = rnd.next(0, 100);
            Y = rnd.next(0, 100);
            break;
        }
        case 4: {
            // Large coordinates, S < W, even (X+Y)
            W = rnd.next(2, 10000);
            S = rnd.next(1, W - 1);
            X = rnd.next(0, 1000000000);
            Y = rnd.next(0, 1000000000);
            if ( (X + Y) % 2 != 0 ) {
                if (X < 1000000000) X++;
                else X--;
            }
            break;
        }
        case 5: {
            // Medium coordinates, S < W, odd (X+Y)
            W = rnd.next(2, 10000);
            S = rnd.next(1, W - 1);
            X = rnd.next(0, 1000);
            Y = rnd.next(0, 1000);
            if ( (X + Y) % 2 == 0 ) {
                if (X < 1000) X++;
                else X--;
            }
            break;
        }
        case 6: {
            // One coordinate is zero (including possibly both zero)
            W = rnd.next(1, 10000);
            S = rnd.next(1, 10000);
            if (rnd.next(0, 1) == 0) {
                X = 0;
                Y = rnd.next(0, 1000000000);
            } else {
                Y = 0;
                X = rnd.next(0, 1000000000);
            }
            break;
        }
        case 7: {
            // X == Y, either small or large; random W,S
            if (rnd.next(0, 1) == 0) {
                X = Y = rnd.next(0, 50);
            } else {
                X = Y = rnd.next(100000000, 1000000000);
            }
            W = rnd.next(1, 10000);
            S = rnd.next(1, 10000);
            break;
        }
        case 8: {
            // Use one of the official examples
            int ex = rnd.next(1, 7);
            if (ex == 1) { X = 4; Y = 2; W = 3; S = 10; }
            else if (ex == 2) { X = 4; Y = 2; W = 3; S = 5; }
            else if (ex == 3) { X = 2; Y = 0; W = 12; S = 10; }
            else if (ex == 4) { X = 25; Y = 18; W = 7; S = 11; }
            else if (ex == 5) { X = 24; Y = 16; W = 12; S = 10; }
            else if (ex == 6) { X = 10000000; Y = 50000000; W = 800; S = 901; }
            else { X = 135; Y = 122; W = 43; S = 29; }
            break;
        }
    }

    println(X, Y, W, S);

    return 0;
}
