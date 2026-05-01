#include "testlib.h"
using namespace std;

long long llabs_ll(long long x) {
    return x < 0 ? -x : x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long x1 = 0, y1 = 0, r1 = 1;
    long long x2 = 0, y2 = 0, r2 = 1;

    int pattern = rnd.next(0, 9);

    switch (pattern) {
        case 0: {
            // Completely random small circles
            x1 = rnd.next(-10, 10);
            y1 = rnd.next(-10, 10);
            r1 = rnd.next(1, 10);
            x2 = rnd.next(-10, 10);
            y2 = rnd.next(-10, 10);
            r2 = rnd.next(1, 10);
            break;
        }
        case 1: {
            // Far apart, definitely no intersection
            r1 = rnd.next(1, 20);
            r2 = rnd.next(1, 20);
            long long d = r1 + r2 + rnd.next(2, 5);
            x1 = 0; y1 = 0;
            x2 = d; y2 = 0;
            break;
        }
        case 2: {
            // External tangent (should be NO)
            r1 = rnd.next(1, 20);
            r2 = rnd.next(1, 20);
            long long d = r1 + r2;
            x1 = 0; y1 = 0;
            x2 = d; y2 = 0;
            break;
        }
        case 3: {
            // Proper intersection (two points)
            while (true) {
                r1 = rnd.next(1, 20);
                r2 = rnd.next(1, 20);
                long long diff = llabs_ll(r1 - r2);
                long long lo = diff + 1;
                long long hi = r1 + r2 - 1;
                if (lo <= hi) {
                    long long d = rnd.next((int)lo, (int)hi);
                    x1 = 0; y1 = 0;
                    x2 = d; y2 = 0;
                    break;
                }
            }
            break;
        }
        case 4: {
            // Internal tangent (one circle inside, touching) -> NO
            do {
                r1 = rnd.next(1, 20);
                r2 = rnd.next(1, 20);
            } while (r1 == r2);
            long long d = llabs_ll(r1 - r2);
            x1 = 0; y1 = 0;
            x2 = d; y2 = 0;
            break;
        }
        case 5: {
            // One circle strictly inside another, not touching (full containment) -> YES
            long long rBig = rnd.next(5, 20);
            long long rSmall = rnd.next(1, (int)(rBig - 2));
            r1 = rBig;
            r2 = rSmall;
            long long maxD = rBig - rSmall - 1; // >=1
            long long d = rnd.next(1, (int)maxD);
            x1 = 0; y1 = 0;
            x2 = d; y2 = 0;
            break;
        }
        case 6: {
            // Coincident circles (identical) -> clearly YES
            x1 = rnd.next(-1000000000, 1000000000);
            y1 = rnd.next(-1000000000, 1000000000);
            r1 = rnd.next(1, 1000000000);
            x2 = x1; y2 = y1; r2 = r1;
            break;
        }
        case 7: {
            // Large coordinates / radii, various relations
            int sub = rnd.next(0, 2);
            if (sub == 0) {
                // Large proper intersection
                r1 = rnd.next(500000000, 900000000);
                r2 = rnd.next(500000000, 900000000);
                long long diff = llabs_ll(r1 - r2);
                long long lo = diff + 1;
                long long hi = r1 + r2 - 1; // <= 1.8e9 - 1
                if (lo > hi) {
                    r1 = r2 = 500000000;
                    diff = 0;
                    lo = 1;
                    hi = r1 + r2 - 1;
                }
                long long d = rnd.next((int)lo, (int)hi);
                x1 = -1000000000; y1 = 0;
                x2 = x1 + d;     y2 = 0;
            } else if (sub == 1) {
                // Large external tangent -> NO
                r1 = rnd.next(800000000, 900000000);
                r2 = rnd.next(800000000, 900000000);
                long long d = r1 + r2; // <= 1.8e9
                x1 = -1000000000; y1 = 0;
                x2 = x1 + d;     y2 = 0;
            } else {
                // Large containment, no touch -> YES
                r1 = rnd.next(800000000, 900000000); // big
                long long maxSmall = r1 - 2;
                if (maxSmall < 1) maxSmall = 1;
                r2 = rnd.next(1, (int)maxSmall);
                long long maxD = r1 - r2 - 1; // >=1
                if (maxD < 1) maxD = 1;
                long long d = rnd.next(1, (int)maxD);
                x1 = -1000000000; y1 = 0;
                x2 = x1 + d;     y2 = 0;
            }
            break;
        }
        case 8: {
            // Nearly external tangent but still disjoint (distance = sum + 1) -> NO
            r1 = rnd.next(5, 50);
            r2 = rnd.next(5, 50);
            long long d = r1 + r2 + 1;
            x1 = 0; y1 = 0;
            x2 = d; y2 = 0;
            break;
        }
        case 9: {
            // Very large radii, almost tangent but overlapping by 1 unit -> YES
            r1 = 1000000000;
            r2 = 1000000000;
            long long d = r1 + r2 - 1; // 2e9 - 1
            x1 = -1000000000; y1 = 0;
            x2 = x1 + d;      y2 = 0;  // 999999999
            break;
        }
    }

    println(x1, y1, r1);
    println(x2, y2, r2);

    return 0;
}
