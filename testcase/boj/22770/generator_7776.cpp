#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases: small to medium
    int n = rnd.next(1, 10);
    println(n);
    for (int i = 0; i < n; i++) {
        // Hyper-parameter: scale category for orbit A
        int scaleA = rnd.next(0, 2);
        int minA = (scaleA == 0 ? 1 : (scaleA == 1 ? 6 : 31));
        int maxA = (scaleA == 0 ? 5 : (scaleA == 1 ? 30 : 100));
        int a1 = rnd.next(minA, maxA);
        int b1;
        // 25% chance to be a circle
        if (rnd.next(0, 3) == 0) {
            b1 = a1;
        } else {
            if (a1 > 1) b1 = rnd.next(1, a1 - 1);
            else b1 = 1;
        }
        // Hyper-parameter: scale category for orbit B
        int scaleB = rnd.next(0, 2);
        int minB = (scaleB == 0 ? 1 : (scaleB == 1 ? 6 : 31));
        int maxB = (scaleB == 0 ? 5 : (scaleB == 1 ? 30 : 100));
        int b2 = rnd.next(minB, maxB);
        int a2;
        // 25% chance to be a circle
        if (rnd.next(0, 3) == 0) {
            a2 = b2;
        } else {
            if (b2 > 1) a2 = rnd.next(1, b2 - 1);
            else a2 = 1;
        }
        // Orbit A must have foci on x-axis: a1 >= b1
        // Orbit B must have foci on y-axis: b2 >= a2
        println(a1, b1);
        println(a2, b2);
    }
    return 0;
}
