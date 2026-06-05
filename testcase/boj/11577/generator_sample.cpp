#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int k;
    vector<int> s;

    if (mode == 0) {
        n = rnd.next(1, 12);
        k = rnd.next(1, n);
        s.assign(n, 0);
    } else if (mode == 1) {
        n = rnd.next(1, 25);
        k = 1;
        s.resize(n);
        for (int i = 0; i < n; ++i) s[i] = rnd.next(0, 1);
    } else if (mode == 2) {
        n = rnd.next(1, 25);
        k = n;
        s.resize(n);
        int pattern = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) {
            if (pattern == 0) s[i] = rnd.next(0, 1);
            else if (pattern == 1) s[i] = 1;
            else s[i] = i % 2;
        }
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        k = rnd.next(2, n);
        s.resize(n);
        for (int i = 0; i < n; ++i) s[i] = i % 2;
        if (rnd.next(0, 1)) {
            for (int i = 0; i < n; ++i) s[i] ^= 1;
        }
    } else if (mode == 4) {
        n = rnd.next(2, 40);
        k = rnd.next(1, n);
        s.assign(n, 0);
        for (int start = 0; start + k <= n; ++start) {
            if (rnd.next(0, 1)) {
                for (int j = start; j < start + k; ++j) s[j] ^= 1;
            }
        }
    } else if (mode == 5) {
        n = rnd.next(20, 80);
        k = rnd.next(1, n);
        s.resize(n);
        int block = rnd.next(1, 7);
        for (int i = 0; i < n; ++i) {
            if (i % block == 0) s[i] = rnd.next(0, 1);
            else s[i] = s[i - 1];
        }
    } else {
        n = rnd.next(1, 60);
        k = rnd.next(1, n);
        s.resize(n);
        int onesBias = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) {
            s[i] = rnd.wnext(2, onesBias);
        }
    }

    println(n, k);
    println(s);

    return 0;
}
