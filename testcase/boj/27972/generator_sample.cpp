#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = rnd.next(1, 24);
    if (rnd.next(0, 9) == 0) m = rnd.next(25, 80);

    vector<long long> p;
    p.reserve(m);

    if (mode == 0) {
        long long cur = rnd.next(1, 1000000000 - m);
        int stepMax = rnd.next(1, 20);
        bool increasing = rnd.next(0, 1);
        for (int i = 0; i < m; ++i) {
            p.push_back(cur);
            cur += rnd.next(1, stepMax);
        }
        if (!increasing) reverse(p.begin(), p.end());
    } else if (mode == 1) {
        long long low = rnd.next(1, 1000);
        long long high = rnd.next(1000000000 - 999, 1000000000);
        for (int i = 0; i < m; ++i) {
            if (i % 2 == 0) p.push_back(low + rnd.next(0, 20));
            else p.push_back(high - rnd.next(0, 20));
        }
        if (rnd.next(0, 1)) reverse(p.begin(), p.end());
    } else if (mode == 2) {
        long long cur = rnd.next(1, 1000000);
        while ((int)p.size() < m) {
            int len = rnd.next(1, min(6, m - (int)p.size()));
            for (int i = 0; i < len; ++i) p.push_back(cur);
            long long delta = rnd.next(1, 50);
            if (cur <= delta || (cur < 1000000000 - delta && rnd.next(0, 1))) cur += delta;
            else cur -= delta;
        }
    } else if (mode == 3) {
        long long cur = rnd.next(1, 1000000000);
        p.push_back(cur);
        for (int i = 1; i < m; ++i) {
            long long delta = rnd.next(0, 100);
            if (delta == 0) {
                p.push_back(cur);
            } else if (cur <= delta) {
                cur += delta;
                p.push_back(cur);
            } else if (cur > 1000000000 - delta) {
                cur -= delta;
                p.push_back(cur);
            } else {
                cur += rnd.next(0, 1) ? delta : -delta;
                p.push_back(cur);
            }
        }
    } else if (mode == 4) {
        int distinct = rnd.next(1, min(8, m));
        vector<long long> vals;
        for (int i = 0; i < distinct; ++i) vals.push_back(rnd.next(1, 1000000000));
        for (int i = 0; i < m; ++i) p.push_back(rnd.any(vals));
    } else {
        long long base = rnd.next(1, 1000000000);
        for (int i = 0; i < m; ++i) p.push_back(base);
    }

    println(m);
    println(p);
    return 0;
}
