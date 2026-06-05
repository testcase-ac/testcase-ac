#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

char randomNonTwoDigit() {
    string digits = "013456789";
    return rnd.any(digits);
}

string randomDigits(int n, int twoWeight) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (rnd.next(100) < twoWeight) {
            s.push_back('2');
        } else {
            s.push_back(rnd.next('0', '9'));
        }
    }
    return s;
}

string separatedRuns(int n) {
    string s;
    while ((int)s.size() < n) {
        int remaining = n - (int)s.size();
        int run = rnd.next(1, min(remaining, rnd.next(1, 12)));
        s.append(run, '2');
        remaining = n - (int)s.size();
        if (remaining > 0) {
            int gap = rnd.next(1, min(remaining, 4));
            for (int i = 0; i < gap; ++i) {
                s.push_back(randomNonTwoDigit());
            }
        }
    }
    return s;
}

string alternatingPattern(int n) {
    string s;
    s.reserve(n);
    int period = rnd.next(2, 7);
    int twoSpan = rnd.next(1, period);
    for (int i = 0; i < n; ++i) {
        if (i % period < twoSpan) {
            s.push_back('2');
        } else {
            s.push_back(randomNonTwoDigit());
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 6) {
        n = rnd.next(100000, 1000000);
    } else {
        n = rnd.next(1, 80);
    }

    string s;
    if (mode == 0) {
        s = randomDigits(n, rnd.next(0, 100));
    } else if (mode == 1) {
        s = string(n, '2');
    } else if (mode == 2) {
        s = separatedRuns(n);
    } else if (mode == 3) {
        s = alternatingPattern(n);
    } else if (mode == 4) {
        s.assign(n, randomNonTwoDigit());
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 20) {
                s[i] = randomNonTwoDigit();
            }
        }
    } else if (mode == 5) {
        s = randomDigits(n, rnd.next(5, 35));
        if (n >= 3) {
            int pos = rnd.next(0, n - 3);
            int len = rnd.next(3, n - pos);
            fill(s.begin() + pos, s.begin() + pos + len, '2');
        }
    } else {
        s = randomDigits(n, rnd.next(40, 90));
    }

    println(n);
    println(s);
    return 0;
}
