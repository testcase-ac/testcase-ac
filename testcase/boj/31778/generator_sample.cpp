#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeBlocks(int n) {
    vector<int> lengths;
    int remaining = n;
    while (remaining > 0) {
        int len = rnd.next(1, min(remaining, 8));
        lengths.push_back(len);
        remaining -= len;
    }

    char ch = rnd.next(2) == 0 ? 'C' : 'P';
    string s;
    for (int len : lengths) {
        s.append(len, ch);
        ch = ch == 'C' ? 'P' : 'C';
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 35);
    if (rnd.next(20) == 0) n = rnd.next(36, 200);

    string s;
    if (mode == 0) {
        s.assign(n, rnd.next(2) == 0 ? 'C' : 'P');
    } else if (mode == 1) {
        char first = rnd.next(2) == 0 ? 'C' : 'P';
        for (int i = 0; i < n; ++i) s += (i % 2 == 0 ? first : (first == 'C' ? 'P' : 'C'));
    } else if (mode == 2) {
        s = makeBlocks(n);
    } else if (mode == 3) {
        int cCount = rnd.next(0, n);
        s.assign(cCount, 'C');
        s.append(n - cCount, 'P');
        if (rnd.next(2) == 0) reverse(s.begin(), s.end());
    } else if (mode == 4) {
        int cPercent = rnd.any(vector<int>{10, 25, 50, 75, 90});
        for (int i = 0; i < n; ++i) s += rnd.next(100) < cPercent ? 'C' : 'P';
    } else {
        s = makeBlocks(n);
        int flips = rnd.next(1, max(1, n / 4));
        for (int i = 0; i < flips; ++i) {
            int pos = rnd.next(n);
            s[pos] = s[pos] == 'C' ? 'P' : 'C';
        }
    }

    int k;
    if (rnd.next(4) == 0) {
        k = rnd.any(vector<int>{1, n});
    } else {
        k = rnd.next(1, n);
    }

    println(n, k);
    println(s);

    return 0;
}
