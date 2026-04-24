#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // We will output exactly one test case: two integers θ1 and θ2.
    // Three kinds: 0 = normal (correct time), 1 = broken by minute angle, 2 = broken by hour angle.

    int kind = rnd.next(0, 2);
    int theta1, theta2;

    if (kind == 0) {
        // Generate a correct time.
        // Minute m must be even so that hour hand angle is integer.
        vector<int> evens;
        for (int m = 0; m < 60; m += 2) evens.push_back(m);
        int m = rnd.any(evens);
        int H = rnd.next(0, 11);
        theta2 = m * 6;             // minute hand
        theta1 = H * 30 + m / 2;    // hour hand
    } else if (kind == 1) {
        // Broken: minute angle not a multiple of 6
        do {
            theta2 = rnd.next(0, 359);
        } while (theta2 % 6 == 0);
        // hour angle arbitrary
        theta1 = rnd.next(0, 359);
    } else {
        // Broken: minute angle valid, but hour angle inconsistent
        vector<int> evens;
        for (int m = 0; m < 60; m += 2) evens.push_back(m);
        int m = rnd.any(evens);
        int H = rnd.next(0, 11);
        theta2 = m * 6;
        int correctH = H * 30 + m / 2;
        // choose wrong hour angle
        do {
            theta1 = rnd.next(0, 359);
        } while (theta1 == correctH);
    }

    println(theta1, theta2);
    return 0;
}
