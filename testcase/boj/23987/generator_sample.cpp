#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeScores(int mode, int n) {
    string s(n, '0');

    if (mode == 0) {
        char digit = char('0' + rnd.next(0, 9));
        fill(s.begin(), s.end(), digit);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) s[i] = char('0' + (i % 10));
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) s[i] = char('0' + ((n - 1 - i) % 10));
    } else if (mode == 3) {
        int low = rnd.next(0, 4);
        int high = rnd.next(max(low + 1, 5), 9);
        for (int i = 0; i < n; ++i) s[i] = char('0' + rnd.next(low, high));
    } else if (mode == 4) {
        int block = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int band = (i / block) % 2;
            int lo = band == 0 ? 0 : 7;
            int hi = band == 0 ? 2 : 9;
            s[i] = char('0' + rnd.next(lo, hi));
        }
    } else {
        for (int i = 0; i < n; ++i) s[i] = char('0' + rnd.next(0, 9));
        int center = rnd.next(0, n - 1);
        int radius = rnd.next(0, min(center, n - 1 - center));
        for (int i = center - radius; i <= center + radius; ++i) {
            s[i] = char('0' + rnd.next(7, 9));
        }
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = tc < 6 ? tc : rnd.next(0, 5);
        int n;
        if (tc == 0) {
            n = 2;
        } else if (tc == 1) {
            n = 3;
        } else if (rnd.next(0, 4) == 0) {
            n = rnd.next(75, 100);
        } else {
            n = rnd.next(2, 30);
        }

        println(n);
        println(makeScores(mode, n));
    }

    return 0;
}
