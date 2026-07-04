#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

string randomBits() {
    string s(128, '0');
    for (char& ch : s) {
        ch = char('0' + rnd.next(0, 1));
    }
    return s;
}

string centerIndependentBits() {
    string s(128, '0');
    for (int mask = 0; mask < 128; ++mask) {
        int paired = mask ^ 8;
        if (mask > paired) {
            continue;
        }
        char value = char('0' + rnd.next(0, 1));
        s[mask] = value;
        s[paired] = value;
    }
    return s;
}

string centerDependentBits() {
    string s = centerIndependentBits();
    int flips = rnd.next(1, 12);
    for (int i = 0; i < flips; ++i) {
        int mask = rnd.next(0, 127);
        s[mask] = char('0' + '1' - s[mask]);
    }
    return s;
}

string popcountPatternBits() {
    int threshold = rnd.next(0, 7);
    bool invert = rnd.next(0, 1);
    string s(128, '0');
    for (int mask = 0; mask < 128; ++mask) {
        int ones = __builtin_popcount((unsigned)mask);
        bool value = ones >= threshold;
        if (invert) {
            value = !value;
        }
        s[mask] = value ? '1' : '0';
    }
    return s;
}

string stridePatternBits() {
    int stride = rnd.next(1, 17);
    int offset = rnd.next(0, stride - 1);
    string s(128, '0');
    for (int i = 0; i < 128; ++i) {
        s[i] = ((i + offset) % stride < (stride + 1) / 2) ? '1' : '0';
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(1, 12);
    for (int i = 0; i < datasets; ++i) {
        int mode = rnd.next(0, 5);
        if (mode == 0) {
            println(centerIndependentBits());
        } else if (mode == 1) {
            println(centerDependentBits());
        } else if (mode == 2) {
            println(popcountPatternBits());
        } else if (mode == 3) {
            println(stridePatternBits());
        } else if (mode == 4) {
            println(string(128, char('0' + rnd.next(0, 1))));
        } else {
            println(randomBits());
        }
    }
    println("#");

    return 0;
}
