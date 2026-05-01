#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with bias toward small / medium, max 20 to keep output small
    int N;
    int r = rnd.next(0, 99);
    if (r < 40)      N = rnd.next(5, 8);
    else if (r < 80) N = rnd.next(9, 14);
    else             N = rnd.next(15, 20);

    // Shape type for diversity
    // 0: general
    // 1: one arm touching side border
    // 2: one leg touching bottom border
    // 3: heart near top (head at row 1)
    int type = rnd.next(0, 3);

    int hr, hc; // heart position, 1-based

    if (type == 3) {
        // Heart fixed near top
        hr = 2;
        hc = rnd.next(2, N - 1);
    } else if (type == 1) {
        // Arm to the side border
        hr = rnd.next(2, N - 2);
        hc = (rnd.next(0, 1) == 0 ? 2 : N - 1);
    } else {
        // General position
        hr = rnd.next(2, N - 2);
        hc = rnd.next(2, N - 1);
    }

    int leftAvail  = hc - 1;     // cells to the left of heart
    int rightAvail = N - hc;     // cells to the right of heart
    int downAvail  = N - hr;     // cells below heart

    // Arms
    int leftArmLen, rightArmLen;
    if (type == 1) {
        // Ensure one arm touches the border
        if (hc == 2) {
            leftArmLen = leftAvail; // == 1
            rightArmLen = rnd.next(1, rightAvail);
        } else {
            rightArmLen = rightAvail; // == 1
            leftArmLen = rnd.next(1, leftAvail);
        }
    } else {
        auto randArm = [&](int avail) -> int {
            if (avail == 1) return 1;
            int mode = rnd.next(0, 2);
            if (mode == 0) return 1;        // minimal
            if (mode == 1) return avail;    // maximal
            return rnd.next(1, avail);      // random
        };
        leftArmLen  = randArm(leftAvail);
        rightArmLen = randArm(rightAvail);
    }

    // Vertical parts: waist and legs
    int waistLen, leftLegLen, rightLegLen;

    if (type == 2) {
        // Make at least one leg reach bottom
        int maxWaist = downAvail - 1; // need at least 1 cell for legs
        waistLen = (maxWaist == 1 ? 1 : rnd.next(1, maxWaist));
        int legMaxAvail = downAvail - waistLen; // >= 1

        int otherLen = (legMaxAvail == 1 ? 1 : rnd.next(1, legMaxAvail));
        if (rnd.next(0, 1) == 0) {
            leftLegLen  = legMaxAvail;
            rightLegLen = otherLen;
        } else {
            rightLegLen = legMaxAvail;
            leftLegLen  = otherLen;
        }
    } else {
        // General case
        if (downAvail == 2) waistLen = 1;
        else waistLen = rnd.next(1, downAvail - 1);

        int legMaxAvail = downAvail - waistLen; // >= 1
        auto randLeg = [&](int avail) -> int {
            if (avail == 1) return 1;
            int mode = rnd.next(0, 2);
            if (mode == 0) return 1;        // minimal
            if (mode == 1) return avail;    // maximal
            return rnd.next(1, avail);      // random
        };
        leftLegLen  = randLeg(legMaxAvail);
        rightLegLen = randLeg(legMaxAvail);
    }

    // Build the board, initially empty
    vector<string> g(N, string(N, '_'));

    // Place head (1 cell) directly above heart
    g[hr - 2][hc - 1] = '*';

    // Place heart
    g[hr - 1][hc - 1] = '*';

    // Place left arm: starts immediately left of heart, extends left
    for (int i = 1; i <= leftArmLen; ++i)
        g[hr - 1][(hc - 1) - i] = '*';

    // Place right arm: starts immediately right of heart, extends right
    for (int i = 1; i <= rightArmLen; ++i)
        g[hr - 1][(hc - 1) + i] = '*';

    // Place waist: starts immediately below heart, extends downward
    for (int i = 1; i <= waistLen; ++i)
        g[(hr - 1) + i][hc - 1] = '*';

    // Place legs: start one row below waist's end
    int startRow = hr + waistLen + 1; // 1-based row index of first leg cell

    // Left leg: column hc - 1
    for (int i = 0; i < leftLegLen; ++i)
        g[(startRow - 1) + i][(hc - 1) - 1] = '*';

    // Right leg: column hc + 1
    for (int i = 0; i < rightLegLen; ++i)
        g[(startRow - 1) + i][(hc - 1) + 1] = '*';

    // Output
    println(N);
    for (int i = 0; i < N; ++i)
        println(g[i]);

    return 0;
}
