#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomString(int n, int openPercent) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += rnd.next(1, 100) <= openPercent ? '(' : ')';
    }
    return s;
}

string alternatingString(int n, bool startsOpen) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        bool open = (i % 2 == 0) == startsOpen;
        s += open ? '(' : ')';
    }
    return s;
}

string mirroredString(int half) {
    string left = randomString(half, rnd.next(25, 75));
    string s = left;
    for (int i = half - 1; i >= 0; --i) {
        s += left[i] == '(' ? ')' : '(';
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 80);
    if (rnd.next(1, 12) == 1) n = rnd.next(81, 250);

    string s;
    if (mode == 0) {
        s = randomString(n, rnd.next(15, 85));
    } else if (mode == 1) {
        char first = rnd.next(0, 1) ? '(' : ')';
        int split = rnd.next(0, n);
        s.assign(split, first);
        s.append(n - split, first == '(' ? ')' : '(');
    } else if (mode == 2) {
        s = alternatingString(n, rnd.next(0, 1));
    } else if (mode == 3) {
        int pairs = max(1, n / 2);
        s.assign(pairs, '(');
        s.append(pairs, ')');
    } else if (mode == 4) {
        int half = rnd.next(1, 60);
        s = mirroredString(half);
        if (rnd.next(0, 1)) {
            s.insert(s.begin(), rnd.next(0, 1) ? '(' : ')');
        }
    } else {
        vector<int> runs;
        int remaining = n;
        while (remaining > 0) {
            int len = rnd.next(1, min(remaining, 12));
            runs.push_back(len);
            remaining -= len;
        }
        char current = rnd.next(0, 1) ? '(' : ')';
        for (int len : runs) {
            s.append(len, current);
            if (rnd.next(1, 100) <= 80) current = current == '(' ? ')' : '(';
        }
    }

    println(s);
    return 0;
}
