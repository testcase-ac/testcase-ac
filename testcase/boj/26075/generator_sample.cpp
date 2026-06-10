#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string alternatingString(int n, int m, int start) {
    string s;
    int zeroes = n;
    int ones = m;
    int want = start;
    while (zeroes > 0 || ones > 0) {
        if (want == 0 && zeroes > 0) {
            s += '0';
            --zeroes;
        } else if (want == 1 && ones > 0) {
            s += '1';
            --ones;
        } else if (zeroes > 0) {
            s += '0';
            --zeroes;
        } else {
            s += '1';
            --ones;
        }
        want ^= 1;
    }
    return s;
}

string blockString(int n, int m, bool onesFirst) {
    if (onesFirst) return string(m, '1') + string(n, '0');
    return string(n, '0') + string(m, '1');
}

string shuffledString(int n, int m) {
    string s = string(n, '0') + string(m, '1');
    shuffle(s.begin(), s.end());
    return s;
}

void applyAdjacentSwaps(string& s, int swaps) {
    if ((int)s.size() < 2) return;
    for (int i = 0; i < swaps; ++i) {
        int p = rnd.next(0, (int)s.size() - 2);
        swap(s[p], s[p + 1]);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int length;
    if (mode <= 1) {
        length = rnd.next(1, 8);
    } else if (mode <= 4) {
        length = rnd.next(2, 30);
    } else {
        length = rnd.next(30, 80);
    }

    int n;
    if (mode == 0) {
        n = rnd.next(0, 1) ? length : 0;
    } else if (mode == 1) {
        n = rnd.next(0, length);
    } else {
        n = rnd.wnext(length + 1, rnd.next(-2, 2));
    }
    int m = length - n;

    string s;
    string t;
    if (mode == 0) {
        s = blockString(n, m, true);
        t = s;
    } else if (mode == 1) {
        s = blockString(n, m, rnd.next(0, 1));
        t = blockString(n, m, !rnd.next(0, 1));
    } else if (mode == 2) {
        s = alternatingString(n, m, rnd.next(0, 1));
        t = alternatingString(n, m, rnd.next(0, 1));
    } else if (mode == 3) {
        s = blockString(n, m, rnd.next(0, 1));
        t = shuffledString(n, m);
    } else if (mode == 4) {
        s = shuffledString(n, m);
        t = s;
        applyAdjacentSwaps(t, rnd.next(1, min(12, max(1, length - 1))));
    } else {
        s = shuffledString(n, m);
        t = shuffledString(n, m);
    }

    println(n, m);
    println(s);
    println(t);
    return 0;
}
