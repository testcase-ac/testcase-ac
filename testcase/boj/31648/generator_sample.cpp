#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomDigits(int len, bool forceTrailingZero) {
    string s;
    s.reserve(len);
    s.push_back(char('1' + rnd.next(9)));
    for (int i = 1; i < len; ++i) {
        s.push_back(char('0' + rnd.next(10)));
    }
    if (forceTrailingZero) s.back() = '0';
    return s;
}

string randomPalindrome(int len) {
    string s(len, '0');
    for (int i = 0; i < (len + 1) / 2; ++i) {
        int lo = (i == 0 ? 1 : 0);
        char c = char('0' + rnd.next(lo, 9));
        s[i] = c;
        s[len - 1 - i] = c;
    }
    return s;
}

string makeCase() {
    int mode = rnd.next(6);

    if (mode == 0) {
        return to_string(rnd.next(1, 25));
    }

    if (mode == 1) {
        int len = rnd.next(2, 35);
        return randomDigits(len, true);
    }

    if (mode == 2) {
        int len = rnd.next(1, 35);
        return randomPalindrome(len);
    }

    if (mode == 3) {
        vector<string> templates = {
            "1",
            "9",
            "10",
            "11",
            "99",
            "100",
            "101",
            "999",
            "1000",
            "1001",
        };
        string s = rnd.any(templates);
        if (rnd.next(2) && s.size() < 30) s += randomDigits(rnd.next(1, 8), false);
        return s;
    }

    if (mode == 4) {
        int len = rnd.next(20, 80);
        return randomDigits(len, rnd.next(2));
    }

    int len = rnd.next(2, 45);
    string s = randomPalindrome(len);
    int pos = rnd.next(1, len - 1);
    s[pos] = char('0' + rnd.next(10));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);
    for (int i = 0; i < t; ++i) {
        println(makeCase());
    }

    return 0;
}
