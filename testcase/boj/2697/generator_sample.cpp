#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomDigits(int len, bool allowZeroHeavy) {
    string s;
    s += char('1' + rnd.next(9));
    for (int i = 1; i < len; ++i) {
        if (allowZeroHeavy && rnd.next(100) < 45)
            s += '0';
        else
            s += char('0' + rnd.next(10));
    }
    return s;
}

string descendingDigits(int len) {
    vector<char> digits;
    digits.push_back(char('1' + rnd.next(9)));
    for (int i = 1; i < len; ++i)
        digits.push_back(char('0' + rnd.next(10)));
    sort(digits.begin(), digits.end(), greater<char>());
    return string(digits.begin(), digits.end());
}

string repeatedDigits(int len) {
    char first = char('1' + rnd.next(9));
    char second = char('0' + rnd.next(10));
    if (second == first)
        second = char('0' + (second - '0' + 1) % 10);

    string s;
    s += first;
    for (int i = 1; i < len; ++i)
        s += rnd.next(100) < 75 ? first : second;
    return s;
}

string almostDescending(int len) {
    string s = descendingDigits(len);
    if (len >= 2) {
        int pos = rnd.next(max(1, len - 5), len - 1);
        swap(s[pos - 1], s[pos]);
        if (s[0] == '0')
            swap(s[0], s[pos]);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 24);
    vector<string> cases;
    cases.reserve(t);

    while ((int)cases.size() < t) {
        int mode = rnd.next(6);
        int len;
        if (rnd.next(100) < 8)
            len = rnd.next(60, 80);
        else
            len = rnd.next(1, 30);

        if (mode == 0) {
            cases.push_back(randomDigits(len, false));
        } else if (mode == 1) {
            cases.push_back(randomDigits(len, true));
        } else if (mode == 2) {
            cases.push_back(descendingDigits(len));
        } else if (mode == 3) {
            cases.push_back(repeatedDigits(len));
        } else if (mode == 4) {
            cases.push_back(almostDescending(len));
        } else {
            string s = randomDigits(len, true);
            sort(s.begin() + 1, s.end());
            cases.push_back(s);
        }
    }

    println((int)cases.size());
    for (const string& s : cases)
        println(s);

    return 0;
}
