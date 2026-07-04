#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long totalRoomChars = 0;
    int dataset = 1;
    while (true) {
        int w = inf.readInt(0, 50, "W");
        inf.readSpace();
        int h = inf.readInt(0, 50, "H");
        inf.readEoln();

        if (w == 0 && h == 0) {
            break;
        }
        setTestCase(dataset++);
        ensuref(w >= 1 && h >= 1, "W and H must both be positive or both be zero");

        // CHECK: The statement gives a sentinel-terminated sequence without a case count.
        // Cap aggregate room text at the local string-size policy limit.
        totalRoomChars += 2LL * w * h;
        ensuref(totalRoomChars <= 10000000LL,
                "aggregate room characters exceed 10000000");

        int leftGoals = 0, rightGoals = 0;
        int leftLen = 0, rightLen = 0;
        int leftRin = 0, rightRin = 0;
        string rowPattern = "[.#%RL]{" + to_string(w) + "}";

        for (int i = 1; i <= h; ++i) {
            string left = inf.readToken(rowPattern, "RoomL_i");
            inf.readSpace();
            string right = inf.readToken(rowPattern, "RoomR_i");
            inf.readEoln();

            for (char c : left) {
                leftGoals += c == '%';
                leftLen += c == 'L';
                leftRin += c == 'R';
            }
            for (char c : right) {
                rightGoals += c == '%';
                rightLen += c == 'L';
                rightRin += c == 'R';
            }
        }

        ensuref(leftGoals == 1, "left room must contain exactly one goal, found %d", leftGoals);
        ensuref(rightGoals == 1, "right room must contain exactly one goal, found %d", rightGoals);
        ensuref(leftLen == 1, "left room must contain exactly one Len start, found %d", leftLen);
        ensuref(rightRin == 1, "right room must contain exactly one Rin start, found %d", rightRin);
        ensuref(leftRin == 0, "left room must not contain Rin starts, found %d", leftRin);
        ensuref(rightLen == 0, "right room must not contain Len starts, found %d", rightLen);
    }

    inf.readEof();
}
