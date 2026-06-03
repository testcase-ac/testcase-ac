#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomDigits(int length, bool allowLeadingZero) {
    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        int lo = (i == 0 && !allowLeadingZero) ? 1 : 0;
        s.push_back(char('0' + rnd.next(lo, 9)));
    }
    return s;
}

string repeatDigit(char digit, int length) {
    return string(length, digit);
}

string makeSmallCase() {
    int mode = rnd.next(0, 8);
    if (mode == 0) {
        return to_string(rnd.next(1, 9));
    }
    if (mode == 1) {
        return to_string(rnd.next(1, 100000));
    }
    if (mode == 2) {
        return repeatDigit(char('1' + rnd.next(0, 8)), rnd.next(2, 5));
    }
    if (mode == 3) {
        int length = rnd.next(2, 5);
        string s = randomDigits(length, false);
        sort(s.begin(), s.end());
        if (s[0] == '0') {
            swap(s[0], *find_if(s.begin(), s.end(), [](char c) { return c != '0'; }));
        }
        return s;
    }
    if (mode == 4) {
        int length = rnd.next(2, 5);
        string s = randomDigits(length, false);
        sort(s.rbegin(), s.rend());
        return s;
    }
    if (mode == 5) {
        string s = to_string(rnd.next(1, 999));
        s += string(rnd.next(1, 2), '0');
        return s;
    }
    if (mode == 6) {
        return rnd.any(vector<string>{"99999", "100000", "90909", "12345", "54321"});
    }
    int length = rnd.next(2, 5);
    string pattern = rnd.any(vector<string>{"12", "21", "90", "109", "808"});
    string s;
    while ((int)s.size() < length) {
        s += pattern;
    }
    s.resize(length);
    if (s[0] == '0') {
        s[0] = char('1' + rnd.next(0, 8));
    }
    return s;
}

string makeLargeCase() {
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        return to_string(rnd.next(100001, 999999));
    }
    if (mode == 1) {
        return string(rnd.next(6, 30), '9');
    }
    if (mode == 2) {
        return "1" + string(rnd.next(5, 35), '0');
    }
    if (mode == 3) {
        return randomDigits(rnd.next(25, 80), false);
    }
    string s = randomDigits(rnd.next(8, 45), false);
    for (int i = 1; i < (int)s.size(); i += rnd.next(2, 5)) {
        s[i] = '0';
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 100);
    int largeCases = rnd.next(0, min(10, t));
    vector<string> cases;
    cases.reserve(t);

    for (int i = 0; i < largeCases; ++i) {
        cases.push_back(makeLargeCase());
    }
    while ((int)cases.size() < t) {
        cases.push_back(makeSmallCase());
    }

    shuffle(cases.begin(), cases.end());

    println(t);
    for (const string& value : cases) {
        println(value);
    }

    return 0;
}
