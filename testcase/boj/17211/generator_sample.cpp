#include "testlib.h"

#include <string>

using namespace std;

string formatProbability(int cents) {
    return to_string(cents / 100) + "." + char('0' + (cents / 10) % 10) +
           char('0' + cents % 10);
}

int biasedCent() {
    int mode = rnd.next(5);
    if (mode == 0) return 0;
    if (mode == 1) return 100;
    if (mode == 2) return 50;
    if (mode == 3) return rnd.next(0, 10) * 10;
    return rnd.next(0, 100);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int nMode = rnd.next(4);
    int n;
    if (nMode == 0) {
        n = 1;
    } else if (nMode == 1) {
        n = 100;
    } else if (nMode == 2) {
        n = rnd.next(2, 10);
    } else {
        n = rnd.next(11, 100);
    }

    int currentMood = rnd.next(0, 1);
    int goodToGood = biasedCent();
    int badToGood = biasedCent();

    println(n, currentMood);
    println(formatProbability(goodToGood), formatProbability(100 - goodToGood),
            formatProbability(badToGood), formatProbability(100 - badToGood));

    return 0;
}
