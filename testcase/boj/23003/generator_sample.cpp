#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string makeIncreasing(int n) {
    string s;
    while ((int)s.size() < n) {
        int len = min(n - (int)s.size(), rnd.next(1, 26));
        int start = rnd.next(0, 26 - len);
        for (int i = 0; i < len; ++i) {
            s += char('A' + start + i);
        }
    }
    return s;
}

string makeDecreasing(int n) {
    string s;
    while ((int)s.size() < n) {
        int len = min(n - (int)s.size(), rnd.next(1, 26));
        int start = rnd.next(len - 1, 25);
        for (int i = 0; i < len; ++i) {
            s += char('A' + start - i);
        }
    }
    return s;
}

string makePlateaus(int n) {
    string s;
    char c = char('A' + rnd.next(0, 25));
    while ((int)s.size() < n) {
        if (rnd.next(0, 2) == 0) {
            c = char('A' + rnd.next(0, 25));
        } else {
            int delta = rnd.next(-2, 2);
            c = char('A' + max(0, min(25, c - 'A' + delta)));
        }

        int run = min(n - (int)s.size(), rnd.next(1, 5));
        s += string(run, c);
    }
    return s;
}

string makeAlternating(int n) {
    string s;
    char low = char('A' + rnd.next(0, 5));
    char high = char('A' + rnd.next(20, 25));
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            s += char(low + rnd.next(0, min(3, 'Z' - low)));
        } else {
            s += char(high - rnd.next(0, min(3, high - 'A')));
        }
    }
    return s;
}

string makeRandomAlphabet(int n) {
    string s;
    int letters = rnd.next(1, 26);
    int offset = rnd.next(0, 26 - letters);
    for (int i = 0; i < n; ++i) {
        s += char('A' + offset + rnd.next(0, letters - 1));
    }
    return s;
}

string makeCase(int n, int mode) {
    if (mode == 0) return makeIncreasing(n);
    if (mode == 1) return makeDecreasing(n);
    if (mode == 2) return makePlateaus(n);
    if (mode == 3) return makeAlternating(n);
    return makeRandomAlphabet(n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int n;
        if (rnd.next(0, 5) == 0) {
            n = rnd.next(26, 80);
        } else {
            n = rnd.next(1, 30);
        }

        println(n);
        println(makeCase(n, mode));
    }

    return 0;
}
