#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomDigits(int len) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(rnd.next(2) == 0 ? '1' : '5');
    }
    return s;
}

string alternatingDigits(int len, char first) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back((i % 2 == 0) ? first : (first == '1' ? '5' : '1'));
    }
    return s;
}

string blockyDigits(int len) {
    string s;
    while (static_cast<int>(s.size()) < len) {
        char digit = rnd.next(2) == 0 ? '1' : '5';
        int run = rnd.next(1, min(6, len - static_cast<int>(s.size())));
        s.append(run, digit);
    }
    return s;
}

int digitSumMod3(const string& s) {
    int rem = 0;
    for (char c : s) {
        rem = (rem + c - '0') % 3;
    }
    return rem;
}

string withResidue(int len, int targetRem) {
    for (int attempt = 0; attempt < 200; ++attempt) {
        string s = randomDigits(len);
        if (digitSumMod3(s) == targetRem) {
            return s;
        }
    }

    string s(len, '1');
    while (digitSumMod3(s) != targetRem) {
        int pos = rnd.next(len);
        s[pos] = (s[pos] == '1' ? '5' : '1');
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(12, 35);
    vector<string> tests;
    tests.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int len = rnd.next(3, 45);
        int mode = rnd.next(8);
        string s;

        if (mode == 0) {
            s.assign(len, '1');
        } else if (mode == 1) {
            s.assign(len, '5');
        } else if (mode == 2) {
            s = alternatingDigits(len, rnd.next(2) == 0 ? '1' : '5');
        } else if (mode == 3) {
            s = blockyDigits(len);
        } else if (mode == 4) {
            s = randomDigits(len);
            s.back() = '5';
        } else if (mode == 5) {
            s = randomDigits(len);
            s.back() = '1';
        } else {
            s = withResidue(len, mode - 6);
        }

        tests.push_back(s);
    }

    println(static_cast<int>(tests.size()));
    for (const string& s : tests) {
        println(s);
    }

    return 0;
}
