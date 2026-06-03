#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

string shuffledWithCounts(int bCount, int wCount) {
    string s(bCount, 'B');
    s += string(wCount, 'W');
    shuffle(s.begin(), s.end());
    return s;
}

string alternatingString(int n) {
    char first = rnd.next(0, 1) == 0 ? 'B' : 'W';
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += (i % 2 == 0) ? first : (first == 'B' ? 'W' : 'B');
    }
    return s;
}

string runString(int n) {
    string s;
    s.reserve(n);
    char current = rnd.next(0, 1) == 0 ? 'B' : 'W';
    while ((int)s.size() < n) {
        int remaining = n - (int)s.size();
        int runLength = rnd.next(1, min(remaining, rnd.next(1, 8)));
        s += string(runLength, current);
        current = current == 'B' ? 'W' : 'B';
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int pairs = rnd.next(1, 15);
        s = shuffledWithCounts(pairs, pairs);
    } else if (mode == 1) {
        int smaller = rnd.next(0, 14);
        bool moreBlack = rnd.next(0, 1) == 0;
        s = moreBlack ? shuffledWithCounts(smaller + 1, smaller)
                      : shuffledWithCounts(smaller, smaller + 1);
    } else if (mode == 2) {
        int n = rnd.next(1, 30);
        char c = rnd.next(0, 1) == 0 ? 'B' : 'W';
        s = string(n, c);
    } else if (mode == 3) {
        s = alternatingString(rnd.next(1, 30));
    } else if (mode == 4) {
        s = runString(rnd.next(1, 30));
    } else {
        int n = rnd.next(1, 30);
        s.reserve(n);
        for (int i = 0; i < n; ++i) {
            double bias = rnd.next(0.15, 0.85);
            s += rnd.next() < bias ? 'B' : 'W';
        }
    }

    println(s);
    return 0;
}
