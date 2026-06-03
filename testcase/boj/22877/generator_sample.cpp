#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char beats(char c) {
    if (c == 'R') return 'S';
    if (c == 'S') return 'P';
    return 'R';
}

char losesTo(char c) {
    if (c == 'R') return 'P';
    if (c == 'S') return 'R';
    return 'S';
}

string repeatedPattern(int n, const string& pattern) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) s += pattern[i % (int)pattern.size()];
    return s;
}

string randomRuns(int n) {
    string s;
    s.reserve(n);
    const string cards = "RSP";
    char last = rnd.any(cards);
    while ((int)s.size() < n) {
        char c = rnd.any(cards);
        if (rnd.next(0, 3) != 0) c = last;
        int len = rnd.next(1, min(8, n - (int)s.size()));
        s.append(len, c);
        last = c;
    }
    return s;
}

string twoCardSegmented(int n) {
    const string cards = "RSP";
    char a = rnd.any(cards);
    char b = rnd.next(0, 1) ? beats(a) : losesTo(a);
    string s;
    s.reserve(n);
    while ((int)s.size() < n) {
        int len = rnd.next(1, min(10, n - (int)s.size()));
        char c = rnd.next(0, 1) ? a : b;
        s.append(len, c);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 40);
    if (rnd.next(0, 19) == 0) n = rnd.next(100, 500);

    long long t;
    int tMode = rnd.next(0, 4);
    if (tMode == 0) t = 1;
    else if (tMode == 1) t = rnd.next(2, min(n + 5, 60));
    else if (tMode == 2) t = rnd.next(100, 100000);
    else t = rnd.next(900000000LL, 1000000000LL);

    string s;
    if (mode == 0) {
        s = repeatedPattern(n, "RSP");
    } else if (mode == 1) {
        s = repeatedPattern(n, "PSR");
    } else if (mode == 2) {
        s = randomRuns(n);
    } else if (mode == 3) {
        s = twoCardSegmented(n);
    } else if (mode == 4) {
        const string cards = "RSP";
        s.assign(n, rnd.any(cards));
        int changes = rnd.next(1, min(n, 8));
        for (int i = 0; i < changes; ++i) s[rnd.next(0, n - 1)] = rnd.any(cards);
    } else if (mode == 5) {
        s = repeatedPattern(n, rnd.next(0, 1) ? "RS" : "SP");
    } else {
        const string cards = "RSP";
        s.reserve(n);
        for (int i = 0; i < n; ++i) s += rnd.any(cards);
    }

    println(n, t);
    println(s);
    return 0;
}
