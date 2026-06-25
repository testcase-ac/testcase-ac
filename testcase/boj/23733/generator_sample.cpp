#include "testlib.h"

#include <string>

using namespace std;

string makeDigits(int n, int mode) {
    string s;
    s.reserve(n);

    if (mode == 0) {
        s.push_back(char('1' + rnd.next(9)));
        for (int i = 1; i < n; ++i) {
            s.push_back(char('0' + rnd.next(10)));
        }
    } else if (mode == 1) {
        char digit = char('1' + rnd.next(9));
        s.assign(n, digit);
    } else if (mode == 2) {
        s.push_back(char('1' + rnd.next(9)));
        for (int i = 1; i < n; ++i) {
            s.push_back(rnd.next(4) == 0 ? char('1' + rnd.next(9)) : '0');
        }
    } else if (mode == 3) {
        s.push_back(char('1' + rnd.next(9)));
        for (int i = 1; i < n; ++i) {
            s.push_back(i % 2 == 0 ? char('7' + rnd.next(3)) : char('0' + rnd.next(3)));
        }
    } else {
        s.push_back(char('1' + rnd.next(9)));
        for (int i = 1; i < n; ++i) {
            int center = (9 * i) / max(1, n - 1);
            int lo = max(0, center - 2);
            int hi = min(9, center + 2);
            s.push_back(char('0' + rnd.next(lo, hi)));
        }
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t;
    int batchMode = rnd.next(6);
    if (batchMode == 0) {
        t = rnd.next(1, 3);
    } else if (batchMode == 1) {
        t = rnd.next(8, 20);
    } else {
        t = rnd.next(3, 10);
    }

    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int sizeMode = rnd.next(5);
        int n;
        if (sizeMode == 0) {
            n = rnd.next(2, 4);
        } else if (sizeMode == 1) {
            n = rnd.next(15, 18);
        } else {
            n = rnd.next(5, 14);
        }

        int kMode = rnd.next(4);
        int k;
        if (kMode == 0) {
            k = 1;
        } else if (kMode == 1) {
            k = n - 1;
        } else {
            k = rnd.next(1, n - 1);
        }

        string digits = makeDigits(n, rnd.next(5));
        println(n, k);
        println(digits);
    }

    return 0;
}
