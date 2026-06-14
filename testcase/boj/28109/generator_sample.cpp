#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

string makeString(int n, int mode) {
    string s;
    s.reserve(n);

    if (mode == 0) {
        char c = rnd.next(0, 1) == 0 ? 'A' : 'Z';
        s.assign(n, c);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) s.push_back(char('A' + (i % 26)));
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) s.push_back(rnd.any(string("ABCXYZ")));
    } else {
        for (int i = 0; i < n; ++i) s.push_back(char('A' + rnd.next(0, 25)));
    }

    if (n >= 2 && rnd.next(0, 3) == 0) {
        s[0] = rnd.any(string("AZ"));
        s[n - 1] = rnd.any(string("AZ"));
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 5);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode <= 2) {
        n = rnd.next(2, 8);
    } else if (sizeMode <= 4) {
        n = rnd.next(9, 30);
    } else {
        n = rnd.next(31, 80);
    }

    string s = makeString(n, rnd.next(0, 3));
    int candidateCount = 25 * n + 1;

    int kMode = rnd.next(0, 7);
    int k;
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = min(candidateCount, 1000000000);
    } else if (kMode == 2) {
        k = min(candidateCount + 1, 1000000000);
    } else if (kMode == 3) {
        k = 1000000000;
    } else if (kMode == 4) {
        k = rnd.next(1, min(candidateCount, 1000000000));
    } else if (kMode == 5) {
        int lo = max(1, candidateCount - 5);
        int hi = min(1000000000, candidateCount + 5);
        k = rnd.next(lo, hi);
    } else {
        k = rnd.next(1, 1000000000);
    }

    println(n, k);
    println(s);

    return 0;
}
