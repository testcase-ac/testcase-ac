#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char randomUpper(char lo = 'A', char hi = 'Z') {
    return char('A' + rnd.next(int(lo - 'A'), int(hi - 'A')));
}

string randomString(int n, char hi) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(randomUpper('A', hi));
    }
    return s;
}

string repeatedRuns(int n) {
    string s;
    while ((int)s.size() < n) {
        char c = randomUpper('A', rnd.next(0, 3) == 0 ? 'Z' : 'D');
        int len = rnd.next(1, min(6, n - (int)s.size()));
        s.append(len, c);
    }
    return s;
}

string parityPattern(int n) {
    char even = randomUpper('A', 'D');
    char odd = randomUpper('A', 'D');
    if (rnd.next(0, 1) && odd == even) {
        odd = char('A' + (odd - 'A' + 1) % 4);
    }

    string s(n, 'A');
    for (int i = 0; i < n; ++i) {
        char base = (i % 2 == 0) ? even : odd;
        s[i] = rnd.next(0, 5) == 0 ? randomUpper('A', 'F') : base;
    }
    return s;
}

string mirroredPattern(int n) {
    string half = randomString((n + 1) / 2, rnd.next(0, 1) ? 'D' : 'Z');
    string s = half;
    for (int i = n / 2 - 1; (int)s.size() < n && i >= 0; --i) {
        s.push_back(half[i]);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    string s;

    if (mode == 0) {
        n = rnd.next(1, 4);
        s = randomString(n, rnd.next(0, 1) ? 'B' : 'Z');
    } else if (mode == 1) {
        n = rnd.next(5, 30);
        s = repeatedRuns(n);
    } else if (mode == 2) {
        n = rnd.next(6, 40);
        s = parityPattern(n);
    } else if (mode == 3) {
        n = rnd.next(5, 35);
        s = mirroredPattern(n);
    } else if (mode == 4) {
        n = rnd.next(20, 80);
        s = randomString(n, rnd.next(0, 2) == 0 ? 'C' : 'Z');
    } else {
        n = rnd.next(80, 200);
        s.assign(n, randomUpper('A', 'C'));
    }

    println(s);
    return 0;
}
