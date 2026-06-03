#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_VALUE = 1000000000LL;

    int t = rnd.next(4, 9);
    vector<vector<int>> allC;
    vector<vector<long long>> allW;
    vector<long long> allK;

    for (int tc = 0; tc < t; ++tc) {
        int mode = tc % 5;
        int n = rnd.next(2, 14);
        vector<int> c(n);
        vector<long long> w(n);
        long long k = rnd.next(0, 25);

        if (mode == 0) {
            if (n % 2 == 1) --n;
            n = max(n, 2);
            c.assign(n, 1);
            w.assign(n, 0);
            for (int i = 0; i < n; ++i) {
                c[i] = i % 2 + 1;
                w[i] = rnd.next(0, 10);
            }
            if (rnd.next(2)) reverse(c.begin(), c.end());
            k = rnd.next(0, 8);
        } else if (mode == 1) {
            c.assign(n, rnd.next(1, 2));
            w.assign(n, 0);
            for (int i = 0; i < n; ++i) w[i] = rnd.next(0, 6);
            k = rnd.next(0, 3);
        } else if (mode == 2) {
            c.assign(n, 1);
            w.assign(n, 0);
            int split = rnd.next(1, n - 1);
            for (int i = split; i < n; ++i) c[i] = 2;
            for (int i = 0; i < n; ++i) w[i] = rnd.next(0, 20);
            k = rnd.next(0, 30);
        } else if (mode == 3) {
            c.assign(n, 1);
            w.assign(n, 0);
            for (int i = 0; i < n; ++i) {
                c[i] = rnd.next(1, 2);
                w[i] = rnd.next(3) == 0 ? MAX_VALUE : rnd.next(0, 12);
            }
            k = rnd.any(vector<long long>{0LL, 1LL, MAX_VALUE, rnd.next(0, 20)});
        } else {
            c.assign(n, 1);
            w.assign(n, 1);
            for (int i = 0; i < n; ++i) {
                c[i] = rnd.next(1, 2);
                if (rnd.next(4) == 0) w[i] = rnd.next(0, 4);
            }
            k = rnd.next(0, 2);
        }

        allC.push_back(c);
        allW.push_back(w);
        allK.push_back(k);
    }

    println(t);
    for (int tc = 0; tc < t; ++tc) {
        println((int)allC[tc].size(), allK[tc]);
        println(allC[tc]);
        println(allW[tc]);
    }

    return 0;
}
