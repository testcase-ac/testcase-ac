#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int makeNumber(int length, const string& digits, bool allowLeadingZero) {
    string s;
    for (int i = 0; i < length; ++i) {
        char c = rnd.any(digits);
        if (i == 0 && !allowLeadingZero) {
            while (c == '0') {
                c = rnd.any(digits);
            }
        }
        s += c;
    }
    return stoi(s);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> anchors = {
        1, 2, 5, 6, 8, 9, 10, 11, 12, 15, 16, 18, 19, 20, 50, 60, 66, 68, 69,
        80, 88, 89, 90, 96, 99, 100, 101, 109, 609, 906, 999999, 1000000};
    const vector<string> digitSets = {
        "0125689", "689", "125", "019", "028", "66669999"};

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(anchors));
        }
    } else if (mode == 1) {
        n = rnd.next(6, 20);
        string digits = rnd.any(digitSets);
        int maxLen = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(1, maxLen);
            a.push_back(makeNumber(len, digits, false));
        }
    } else if (mode == 2) {
        n = rnd.next(8, 24);
        int base = rnd.any(anchors);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                a.push_back(base);
            } else {
                a.push_back(rnd.any(anchors));
            }
        }
    } else if (mode == 3) {
        n = rnd.next(4, 16);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(1, 6);
            a.push_back(makeNumber(len, "01689", false));
        }
    } else if (mode == 4) {
        n = rnd.next(5, 18);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(1, 6);
            string digits = (i % 2 == 0) ? "012" : "5689";
            a.push_back(makeNumber(len, digits, false));
        }
    } else {
        n = rnd.next(10, 24);
        for (int i = 0; i < n; ++i) {
            int len = rnd.wnext(6, -2) + 1;
            a.push_back(makeNumber(len, "0125689", false));
        }
    }

    shuffle(a.begin(), a.end());
    println((int)a.size());
    println(a);

    return 0;
}
