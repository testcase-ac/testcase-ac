#include "testlib.h"

#include <string>

using namespace std;

string randomBinary(int len) {
    string s = "1";
    for (int i = 1; i < len; ++i) {
        s += char('0' + rnd.next(0, 1));
    }
    return s;
}

string patternedBinary(int len, int mode) {
    string s = "1";
    for (int i = 1; i < len; ++i) {
        if (mode == 0) {
            s += '0';
        } else if (mode == 1) {
            s += '1';
        } else if (mode == 2) {
            s += char('0' + (i % 2));
        } else {
            s += char('0' + ((i + 1) % 2));
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string start;
    string target;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        start = "1";
        target = rnd.next(0, 1) == 0 ? "1" : randomBinary(rnd.next(1, 3));
    } else if (mode == 1) {
        int len = rnd.next(2, 10);
        start = randomBinary(len);
        target = start;
        int flips = rnd.next(1, len - 1);
        for (int i = 0; i < flips; ++i) {
            int pos = rnd.next(1, len - 1);
            target[pos] = target[pos] == '0' ? '1' : '0';
        }
    } else if (mode == 2) {
        int len = rnd.next(1, 9);
        start = patternedBinary(len, rnd.next(0, 3));
        target = patternedBinary(len + 1, rnd.next(0, 3));
    } else if (mode == 3) {
        int len = rnd.next(2, 10);
        start = patternedBinary(len, rnd.next(0, 3));
        target = patternedBinary(rnd.next(1, len), rnd.next(0, 3));
    } else if (mode == 4) {
        start = patternedBinary(10, rnd.next(0, 3));
        target = patternedBinary(rnd.next(8, 10), rnd.next(0, 3));
    } else {
        start = randomBinary(rnd.next(1, 10));
        target = randomBinary(rnd.next(1, 10));
    }

    println(start);
    println(target);
    return 0;
}
