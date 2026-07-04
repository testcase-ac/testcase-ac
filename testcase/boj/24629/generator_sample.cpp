#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

char randomHexDigit(bool allowZero) {
    const string digits = allowZero ? "0123456789ABCDEF" : "123456789ABCDEF";
    return rnd.any(digits);
}

string randomHexString(int length) {
    string s;
    s.reserve(length);
    s.push_back(randomHexDigit(false));
    for (int i = 1; i < length; ++i) {
        s.push_back(randomHexDigit(true));
    }
    return s;
}

string patternedHexString(int length, const string& alphabet) {
    string s;
    s.reserve(length);
    do {
        s.clear();
        for (int i = 0; i < length; ++i) {
            s.push_back(rnd.any(alphabet));
        }
    } while (s[0] == '0');
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string n;
    int k;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = randomHexString(rnd.next(1, 4));
        k = rnd.next(0, 16);
    } else if (mode == 1) {
        n = patternedHexString(rnd.next(2, 24), "0123789F");
        k = rnd.next(0, min(1000, 4 * (int)n.size() + 4));
    } else if (mode == 2) {
        int length = rnd.next(1, 40);
        n = string(length, '0');
        n[0] = rnd.any(string("1248"));
        int tweaks = rnd.next(0, min(5, length - 1));
        for (int i = 0; i < tweaks; ++i) {
            n[rnd.next(1, length - 1)] = randomHexDigit(true);
        }
        k = rnd.next(0, min(1000, 4 * length + 8));
    } else if (mode == 3) {
        int length = rnd.next(20, 250);
        n = patternedHexString(length, "0F");
        if (n[0] == '0') {
            n[0] = 'F';
        }
        k = rnd.next(0, 1000);
    } else if (mode == 4) {
        int length = rnd.next(1, 250);
        n = randomHexString(length);
        int bitLimit = min(1000, 4 * length);
        k = rnd.next(max(0, bitLimit - 10), bitLimit);
    } else {
        int length = rnd.next(1, 250);
        n = string(length, 'F');
        k = rnd.next(0, 1000);
    }

    println(n);
    println(k);

    return 0;
}
