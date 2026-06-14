#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_VALUE = 2000000000;

int boundedXorPartner(int x, int cap) {
    for (int attempt = 0; attempt < 100; ++attempt) {
        int a = rnd.next(0, cap);
        int b = a ^ x;
        if (0 <= b && b <= MAX_VALUE) return a;
    }
    return x <= MAX_VALUE ? 0 : rnd.next(0, cap);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 10);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(2, 14);
        int x = 0;
        vector<int> v;

        if (mode == 0) {
            x = 0;
            int distinct = rnd.next(1, 4);
            for (int i = 0; i < n; ++i) v.push_back(rnd.next(0, distinct - 1));
        } else if (mode == 1) {
            x = rnd.next(0, 31);
            for (int i = 0; i + 1 < n; i += 2) {
                int a = rnd.next(0, 63);
                v.push_back(a);
                v.push_back(a ^ x);
            }
            if ((int)v.size() < n) v.push_back(rnd.next(0, 63));
        } else if (mode == 2) {
            x = rnd.next(0, MAX_VALUE);
            int cap = rnd.next(1000000000, MAX_VALUE);
            for (int i = 0; i + 1 < n; i += 2) {
                int a = boundedXorPartner(x, cap);
                v.push_back(a);
                v.push_back(a ^ x);
            }
            if ((int)v.size() < n) v.push_back(rnd.next(0, MAX_VALUE));
        } else if (mode == 3) {
            x = rnd.next(0, 1023);
            int base = rnd.next(0, 1 << rnd.next(1, 10));
            for (int i = 0; i < n; ++i) v.push_back(base ^ rnd.next(0, 1023));
        } else {
            x = rnd.next(0, MAX_VALUE);
            for (int i = 0; i < n; ++i) {
                if (rnd.next(0, 3) == 0) {
                    v.push_back(rnd.next(0, 31));
                } else {
                    v.push_back(rnd.next(0, MAX_VALUE));
                }
            }
        }

        shuffle(v.begin(), v.end());
        println(n, x);
        println(v);
    }

    return 0;
}
