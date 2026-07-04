#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makePattern(int n, int mode) {
    string s(n, '0');

    if (mode == 0) {
        fill(s.begin(), s.end(), rnd.next(0, 1) ? '1' : '0');
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) s[i] = (i % 2 == 0 ? '0' : '1');
        if (rnd.next(0, 1)) {
            for (char& c : s) c = (c == '0' ? '1' : '0');
        }
    } else if (mode == 2) {
        int block = rnd.next(1, max(1, min(n, 8)));
        char bit = rnd.next(0, 1) ? '1' : '0';
        for (int i = 0; i < n; ++i) {
            if (i % block == 0 && rnd.next(0, 2) == 0) bit = (bit == '0' ? '1' : '0');
            s[i] = bit;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) s[i] = (rnd.next(0, 99) < 20 ? '1' : '0');
    } else {
        for (int i = 0; i < n; ++i) s[i] = (rnd.next(0, 1) ? '1' : '0');
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> sizes = {1, 2, 3, 4, 5, 8, 13, 21, 32};
    int n;
    if (rnd.next(0, 4) == 0) {
        n = rnd.next(1, 60);
    } else {
        n = rnd.any(sizes);
    }

    string initial = makePattern(n, rnd.next(0, 4));
    string target = makePattern(n, rnd.next(0, 4));

    if (rnd.next(0, 5) == 0) {
        target = initial;
    } else if (rnd.next(0, 4) == 0) {
        int changes = rnd.next(1, min(n, 6));
        for (int i = 0; i < changes; ++i) {
            int pos = rnd.next(0, n - 1);
            target[pos] = (target[pos] == '0' ? '1' : '0');
        }
    }

    println(n);
    println(initial);
    println(target);

    return 0;
}
