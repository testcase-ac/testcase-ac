#include "testlib.h"

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

string formatCoins(int cents) {
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%d.%02d", cents / 100, cents % 100);
    return string(buffer);
}

int randomPositiveSolved() {
    if (rnd.next(4) == 0) return 24;
    return rnd.next(1, 23);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> coinChoices = {0, 1, 50, 98, 99, 100, 197, 198, 199, 500};
    int cents = rnd.any(coinChoices);
    if (rnd.next(3) == 0) cents = rnd.next(0, 500);

    int mode = rnd.next(6);
    int n = rnd.next(1, 40);
    if (mode == 5) n = rnd.next(60, 120);

    vector<int> solved(n);
    if (mode == 0) {
        for (int i = 0; i < n; ++i) solved[i] = 0;
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) solved[i] = randomPositiveSolved();
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int block = i % rnd.next(3, 7);
            solved[i] = (block == 0 ? 0 : randomPositiveSolved());
        }
    } else if (mode == 3) {
        int zeroStart = rnd.next(0, n - 1);
        int zeroLen = rnd.next(1, min(5, n - zeroStart));
        for (int i = 0; i < n; ++i) solved[i] = randomPositiveSolved();
        for (int i = zeroStart; i < zeroStart + zeroLen; ++i) solved[i] = 0;
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            solved[i] = (rnd.next(100) < 45 ? 0 : randomPositiveSolved());
        }
    } else {
        for (int i = 0; i < n; ++i) {
            if (i % 10 == 0 || i % 10 == 1 || rnd.next(100) < 15) {
                solved[i] = 0;
            } else {
                solved[i] = rnd.next(1, 24);
            }
        }
    }

    println(formatCoins(cents));
    println(n);
    println(solved);

    return 0;
}
