#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeDirections(int n, int mode) {
    string s(n, 'L');

    if (mode == 0) {
        fill(s.begin(), s.end(), rnd.next(0, 1) == 0 ? 'L' : 'R');
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            s[i] = (i % 2 == rnd.next(0, 1)) ? 'L' : 'R';
        }
    } else if (mode == 2) {
        int split = rnd.next(0, n);
        for (int i = 0; i < n; ++i) {
            s[i] = i < split ? 'L' : 'R';
        }
    } else if (mode == 3) {
        int block = rnd.next(1, max(1, min(n, 5)));
        for (int i = 0; i < n; ++i) {
            s[i] = ((i / block) % 2 == 0) ? 'L' : 'R';
        }
    } else {
        for (int i = 0; i < n; ++i) {
            s[i] = rnd.next(0, 1) == 0 ? 'L' : 'R';
        }
    }

    if (rnd.next(0, 3) == 0) {
        reverse(s.begin(), s.end());
    }
    return s;
}

vector<long long> makeHeights(int n, int mode) {
    vector<long long> h(n);

    if (mode == 0) {
        long long start = rnd.next(1LL, 20LL);
        long long step = rnd.next(1LL, 7LL);
        for (int i = 0; i < n; ++i) {
            h[i] = min(1000000000LL, start + step * i);
        }
    } else if (mode == 1) {
        long long start = rnd.next(1LL, 20LL);
        long long step = rnd.next(1LL, 7LL);
        for (int i = 0; i < n; ++i) {
            h[i] = max(1LL, start + step * (n - 1 - i));
        }
    } else if (mode == 2) {
        int distinct = rnd.next(1, min(n, 6));
        vector<long long> values;
        for (int i = 0; i < distinct; ++i) {
            values.push_back(rnd.next(1LL, 30LL));
        }
        for (int i = 0; i < n; ++i) {
            h[i] = rnd.any(values);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                h[i] = 1000000000LL - rnd.next(0LL, 5LL);
            } else {
                h[i] = rnd.next(1LL, 12LL);
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            h[i] = (i % 2 == 0) ? rnd.next(1LL, 5LL) : rnd.next(999999995LL, 1000000000LL);
        }
    } else {
        long long lo = rnd.next(1LL, 50LL);
        long long hi = rnd.next(lo, min(1000000000LL, lo + rnd.next(0LL, 100LL)));
        for (int i = 0; i < n; ++i) {
            h[i] = rnd.next(lo, hi);
        }
    }

    if (rnd.next(0, 4) == 0) {
        shuffle(h.begin(), h.end());
    }
    return h;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int sizeMode = rnd.next(0, 9);
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode <= 6) {
        n = rnd.next(2, 20);
    } else if (sizeMode <= 8) {
        n = rnd.next(21, 80);
    } else {
        n = rnd.next(100, 300);
    }

    int directionMode = rnd.next(0, 4);
    int heightMode = rnd.next(0, 5);

    println(n);
    println(makeDirections(n, directionMode));
    println(makeHeights(n, heightMode));

    return 0;
}
