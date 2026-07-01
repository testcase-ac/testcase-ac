#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomDigits(int len) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(char('0' + rnd.next(10)));
    }
    return s;
}

string repeatedDigit(int len) {
    char digit = char('0' + rnd.next(10));
    return string(len, digit);
}

string alternatingDigits(int len) {
    char a = char('0' + rnd.next(10));
    char b = char('0' + rnd.next(10));
    if (a == b) b = char('0' + (b - '0' + 1) % 10);

    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(i % 2 == 0 ? a : b);
    }
    return s;
}

string leadingZeroDigits(int len) {
    string s = randomDigits(len);
    int zeroPrefix = rnd.next(1, len);
    for (int i = 0; i < zeroPrefix; ++i) {
        s[i] = '0';
    }
    return s;
}

string biasedUglyDigits(int len) {
    const string pool = "00223557789";
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(pool[rnd.next((int)pool.size())]);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(8, 18);
    vector<string> cases;
    cases.reserve(n);

    for (int tc = 0; tc < n; ++tc) {
        int mode = rnd.next(6);
        int len;
        if (tc == 0 && rnd.next(2) == 0) {
            len = 40;
        } else if (mode == 0) {
            len = 1;
        } else if (mode <= 3) {
            len = rnd.next(2, 12);
        } else {
            len = rnd.next(13, 30);
        }

        if (mode == 0) {
            cases.push_back(randomDigits(len));
        } else if (mode == 1) {
            cases.push_back(leadingZeroDigits(len));
        } else if (mode == 2) {
            cases.push_back(repeatedDigit(len));
        } else if (mode == 3) {
            cases.push_back(alternatingDigits(len));
        } else if (mode == 4) {
            cases.push_back(biasedUglyDigits(len));
        } else {
            cases.push_back(randomDigits(len));
        }
    }

    println(n);
    for (const string& s : cases) {
        println(s);
    }

    return 0;
}
