#include "testlib.h"

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

string shuffledDigits(string s) {
    shuffle(s.begin(), s.end());
    return s;
}

string randomDigits(int len, bool allowAllZero) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(char('0' + rnd.next(0, 9)));
    }

    if (!allowAllZero) {
        bool allZero = true;
        for (char ch : s) {
            if (ch != '0') {
                allZero = false;
                break;
            }
        }
        if (allZero) {
            s[rnd.next(len)] = char('1' + rnd.next(0, 8));
        }
    }

    return s;
}

string makeCase() {
    int mode = rnd.next(0, 7);
    int len = rnd.next(2, 16);

    if (mode == 0) {
        len = 3;
        return randomDigits(len, false);
    }

    if (mode == 1) {
        return shuffledDigits("00");
    }

    if (mode == 2) {
        string s(len, '0');
        s[rnd.next(len)] = char('1' + rnd.next(0, 8));
        return shuffledDigits(s);
    }

    if (mode == 3) {
        char d = char('1' + rnd.next(0, 8));
        string s(len, d);
        if (len > 2 && rnd.next(0, 1)) {
            s[rnd.next(len)] = '0';
        }
        return shuffledDigits(s);
    }

    if (mode == 4) {
        string s;
        s.reserve(len);
        int high = rnd.next(7, 9);
        for (int i = 0; i < len; ++i) {
            s.push_back(char('0' + rnd.next(0, high)));
        }
        if (len > 2) {
            s[rnd.next(len)] = char('1' + rnd.next(0, high - 1));
        }
        return shuffledDigits(s);
    }

    if (mode == 5) {
        string s;
        s.reserve(len);
        vector<char> pool = {'0', '0', '1', '1', '8', '9', '9'};
        for (int i = 0; i < len; ++i) {
            s.push_back(rnd.any(pool));
        }
        if (len > 2) {
            s[rnd.next(len)] = char('1' + rnd.next(0, 8));
        }
        return shuffledDigits(s);
    }

    if (mode == 6) {
        string s = "0123456789";
        while ((int)s.size() < len) {
            s.push_back(char('0' + rnd.next(0, 9)));
        }
        s.resize(len);
        return shuffledDigits(s);
    }

    return randomDigits(len, len <= 2);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 25);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        std::printf("\n");
        println(makeCase());
    }

    return 0;
}
