#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

const int MAX_S = 2147483647;

int makeValue(int twos, int fives) {
    int64_t value = 1;
    for (int i = 0; i < twos && value * 2 <= MAX_S; ++i) {
        value *= 2;
    }
    for (int i = 0; i < fives && value * 5 <= MAX_S; ++i) {
        value *= 5;
    }

    vector<int> multipliers = {1, 3, 7, 9, 11, 13, 17, 19, 21, 27, 31};
    shuffle(multipliers.begin(), multipliers.end());
    for (int m : multipliers) {
        if (value * m <= MAX_S) {
            return static_cast<int>(value * m);
        }
    }
    return static_cast<int>(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 5);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        if (mode == 5) {
            n = rnd.next(40, 120);
        } else if (rnd.next(0, 4) == 0) {
            n = rnd.next(2, 6);
        } else {
            n = rnd.next(7, 30);
        }

        int k;
        if (rnd.next(0, 5) == 0) {
            k = 1;
        } else if (rnd.next(0, 4) == 0) {
            k = min(20, n - 1);
        } else {
            k = rnd.next(1, min(20, n - 1));
        }

        vector<int> s(n);
        for (int i = 0; i < n; ++i) {
            int twos = 0;
            int fives = 0;

            if (mode == 0) {
                twos = rnd.next(0, 3);
                fives = rnd.next(0, 3);
            } else if (mode == 1) {
                twos = (i % 2 == 0 ? rnd.next(0, 1) : rnd.next(4, 12));
                fives = (i % 2 == 0 ? rnd.next(4, 12) : rnd.next(0, 1));
            } else if (mode == 2) {
                twos = rnd.next(0, 20);
                fives = rnd.next(0, 8);
            } else if (mode == 3) {
                twos = rnd.next(0, 8);
                fives = rnd.next(0, 13);
            } else if (mode == 4) {
                int distanceBias = min(i, n - 1 - i);
                twos = rnd.next(0, 2) + (distanceBias % 3 == 0 ? rnd.next(3, 8) : 0);
                fives = rnd.next(0, 2) + (distanceBias % 4 == 0 ? rnd.next(3, 8) : 0);
            } else {
                twos = rnd.wnext(30, -3);
                fives = rnd.wnext(13, -2);
            }

            if (rnd.next(0, 25) == 0) {
                s[i] = MAX_S;
            } else if (rnd.next(0, 12) == 0) {
                s[i] = 1;
            } else {
                s[i] = makeValue(twos, fives);
            }
        }

        println(n, k);
        println(s);
    }

    return 0;
}
