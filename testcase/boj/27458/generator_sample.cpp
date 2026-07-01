#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char nonZeroDigit() {
    return char('1' + rnd.next(0, 8));
}

char anyDigit() {
    return char('0' + rnd.next(0, 9));
}

string randomDigits(int len, bool allowLeadingZero) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        if (i == 0 && !allowLeadingZero) {
            s.push_back(nonZeroDigit());
        } else {
            s.push_back(anyDigit());
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    string s;

    if (mode == 0) {
        int prefixLen = rnd.next(0, 10);
        int suffixLen = rnd.next(0, 18 - prefixLen - 3);
        s = randomDigits(prefixLen, false) + "666" + randomDigits(suffixLen, true);
    } else if (mode == 1) {
        int len = rnd.next(3, 18);
        int pos = rnd.next(0, len - 3);
        s = randomDigits(len, false);
        s.replace(pos, 3, "666");
    } else if (mode == 2) {
        int runLen = rnd.next(3, 12);
        int prefixLen = rnd.next(0, min(3, 18 - runLen));
        int suffixLen = rnd.next(0, min(3, 18 - prefixLen - runLen));
        s = randomDigits(prefixLen, false) + string(runLen, '6') + randomDigits(suffixLen, true);
    } else if (mode == 3) {
        int len = rnd.next(4, 18);
        int pos = rnd.next(0, len - 3);
        s.assign(len, '0');
        s[0] = nonZeroDigit();
        s.replace(pos, 3, "666");
    } else if (mode == 4) {
        int suffixLen = rnd.next(0, 15);
        s = "666" + randomDigits(suffixLen, true);
    } else if (mode == 5) {
        int prefixLen = rnd.next(1, 15);
        s = randomDigits(prefixLen, false) + "666";
    } else {
        s = randomDigits(15, false) + "666";
        for (int i = 0; i < 3; ++i) {
            s[rnd.next(0, 14)] = char('7' + rnd.next(0, 2));
        }
    }

    while (s.size() > 1 && s[0] == '0') {
        s.erase(s.begin());
    }
    if (s.find("666") == string::npos) {
        s += "666";
    }

    println(s);
    return 0;
}
