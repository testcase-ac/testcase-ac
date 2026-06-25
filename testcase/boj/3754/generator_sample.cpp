#include "testlib.h"
#include <vector>
using namespace std;

static vector<int> makeAllOnes(int n) {
    return vector<int>(n, 1);
}

static vector<int> makeRandomPiles(int n, int lo, int hi) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rnd.next(lo, hi);
    }
    return a;
}

static vector<int> makeXorZero(int n, int hi) {
    vector<int> a;
    while ((int)a.size() < n) {
        int remaining = n - (int)a.size();
        if (remaining != 3) {
            int x = rnd.next(1, hi);
            a.push_back(x);
            a.push_back(x);
            continue;
        }

        int x = rnd.next(1, hi);
        int y = rnd.next(1, hi);
        int z = x ^ y;
        if (z >= 1 && z <= hi) {
            a.push_back(x);
            a.push_back(y);
            a.push_back(z);
        }
    }
    shuffle(a.begin(), a.end());
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(8, 18);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(7);
        vector<int> a;

        if (mode == 0) {
            a = {rnd.next(1, 4747)};
        } else if (mode == 1) {
            int n = rnd.next(1, 47);
            if (tc % 2 == 0 && n < 47) {
                ++n;
            }
            a = makeAllOnes(n);
        } else if (mode == 2) {
            int n = rnd.next(2, 12);
            int hi = rnd.next(3, 30);
            a = makeXorZero(n, hi);
        } else if (mode == 3) {
            int n = rnd.next(2, 12);
            int hi = rnd.next(2, 80);
            a = makeRandomPiles(n, 1, hi);
            int x = 0;
            for (int v : a) {
                x ^= v;
            }
            if (x == 0) {
                a.back() = min(4747, a.back() + 1);
            }
        } else if (mode == 4) {
            int n = rnd.next(2, 10);
            a = makeRandomPiles(n, 4700, 4747);
        } else if (mode == 5) {
            int n = rnd.next(2, 12);
            a = makeAllOnes(n);
            int pos = rnd.next(n);
            a[pos] = rnd.next(2, 20);
        } else {
            int n = rnd.next(2, 15);
            int base = 1 << rnd.next(1, 12);
            a = makeRandomPiles(n, max(1, base - 3), min(4747, base + 3));
        }

        println((int)a.size());
        println(a);
    }

    return 0;
}
