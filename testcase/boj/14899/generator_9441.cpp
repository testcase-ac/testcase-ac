#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    struct Query {
        int type;
        int l;
        int r;
        long long v; // c or d when needed
    };

    // Helper lambdas
    auto genRange = [&](int n) -> pair<int,int> {
        if (n == 1) return {0, 0};
        int style = rnd.next(0, 2); // 0,1,2
        if (style == 0) {
            return make_pair(0, n - 1); // full range
        } else if (style == 1) {
            int l = rnd.next(0, n - 1);
            int maxLen = min(3, n - l);
            int len = rnd.next(1, maxLen);
            int r = l + len - 1;
            return make_pair(l, r);
        } else {
            int l = rnd.next(0, n - 1);
            int r = rnd.next(l, n - 1);
            return make_pair(l, r);
        }
    };

    auto genC = [&]() -> long long {
        int mode = rnd.next(1, 10);
        if (mode <= 5) { // 50% very small
            return rnd.next(-5, 5);
        } else if (mode <= 8) { // 30% medium
            return rnd.next(-100, 100);
        } else { // 20% extreme within limits
            int sgn = rnd.next(0, 1) ? 1 : -1;
            return 1LL * sgn * rnd.next(5000, 10000);
        }
    };

    auto genD = [&]() -> long long {
        int mode = rnd.next(1, 10);
        if (mode <= 4) { // 40% very small
            return rnd.next(2, 5);
        } else if (mode <= 7) { // 30% small/medium
            return rnd.next(6, 20);
        } else if (mode <= 9) { // 20% medium/large
            return rnd.next(21, 1000);
        } else { // 10% huge
            int p = rnd.next(0, 1);
            if (p == 0) return 1000000000;
            else return rnd.next(10001, 1000000000);
        }
    };

    // Choose scenario for initial array
    int scenario = rnd.next(0, 5);
    int n = 0;
    vector<long long> a;

    switch (scenario) {
        case 0: { // very small n, small values
            n = rnd.next(1, 4);
            a.resize(n);
            for (int i = 0; i < n; ++i)
                a[i] = rnd.next(-5, 5);
            break;
        }
        case 1: { // monotone increasing
            n = rnd.next(5, 12);
            a.resize(n);
            long long cur = rnd.next(-5, 5);
            for (int i = 0; i < n; ++i) {
                a[i] = cur;
                cur += rnd.next(0, 5);
            }
            break;
        }
        case 2: { // mix including very large magnitudes
            n = rnd.next(3, 12);
            a.resize(n);
            for (int i = 0; i < n; ++i) {
                int mode = rnd.next(1, 10);
                if (mode <= 4) {
                    a[i] = rnd.next(-20, 20);
                } else if (mode <= 7) {
                    int sgn = rnd.next(0, 1) ? 1 : -1;
                    a[i] = 1LL * sgn * rnd.next(1000, 100000);
                } else {
                    int sgn = rnd.next(0, 1) ? 1 : -1;
                    a[i] = 1LL * sgn * rnd.next(100000000, 1000000000);
                }
            }
            break;
        }
        case 3: { // constant array
            n = rnd.next(1, 12);
            a.resize(n);
            long long val;
            int mode = rnd.next(0, 1);
            if (mode == 0)
                val = rnd.next(-20, 20);
            else {
                int sgn = rnd.next(0, 1) ? 1 : -1;
                val = 1LL * sgn * rnd.next(100000000, 1000000000);
            }
            for (int i = 0; i < n; ++i)
                a[i] = val;
            break;
        }
        case 4: { // alternating signs, small
            n = rnd.next(4, 12);
            a.resize(n);
            for (int i = 0; i < n; ++i) {
                long long base = rnd.next(0, 10);
                a[i] = (i % 2 ? 1 : -1) * base;
            }
            break;
        }
        case 5: { // random small around zero
            n = rnd.next(2, 12);
            a.resize(n);
            for (int i = 0; i < n; ++i)
                a[i] = rnd.next(-30, 30);
            break;
        }
    }

    int maxQ = (n == 1 ? 12 : 15);
    int q = rnd.next(1, maxQ);
    vector<Query> qs(q);

    if (q >= 4) {
        // First ensure all four types appear at least once
        vector<int> base = {1, 2, 3, 4};
        shuffle(base.begin(), base.end());
        for (int i = 0; i < 4; ++i) {
            qs[i].type = base[i];
            auto pr = genRange(n);
            qs[i].l = pr.first;
            qs[i].r = pr.second;
            if (qs[i].type == 1) qs[i].v = genC();
            else if (qs[i].type == 2) qs[i].v = genD();
            else qs[i].v = 0;
        }
        // Remaining queries are random types
        for (int i = 4; i < q; ++i) {
            int rtype = rnd.next(1, 100);
            int type;
            if (rtype <= 30) type = 1;       // add
            else if (rtype <= 55) type = 2;  // divide
            else if (rtype <= 77) type = 3;  // min
            else type = 4;                   // sum

            qs[i].type = type;
            auto pr = genRange(n);
            qs[i].l = pr.first;
            qs[i].r = pr.second;
            if (type == 1) qs[i].v = genC();
            else if (type == 2) qs[i].v = genD();
            else qs[i].v = 0;
        }
    } else {
        // q = 1, 2, or 3: small carefully mixed set
        for (int i = 0; i < q; ++i) {
            int type;
            if (q == 1) {
                // single query: min or sum
                type = (rnd.next(0, 1) ? 3 : 4);
            } else if (q == 2) {
                if (i == 0) type = (rnd.next(0, 1) ? 1 : 2); // update
                else type = (rnd.next(0, 1) ? 3 : 4);        // query
            } else { // q == 3
                if (i == 0) type = 1;
                else if (i == 1) type = 2;
                else type = (rnd.next(0, 1) ? 3 : 4);
            }
            qs[i].type = type;
            auto pr = genRange(n);
            qs[i].l = pr.first;
            qs[i].r = pr.second;
            if (type == 1) qs[i].v = genC();
            else if (type == 2) qs[i].v = genD();
            else qs[i].v = 0;
        }
    }

    // Output
    println(n, q);
    println(a);
    for (int i = 0; i < q; ++i) {
        if (qs[i].type == 1 || qs[i].type == 2)
            println(qs[i].type, qs[i].l, qs[i].r, qs[i].v);
        else
            println(qs[i].type, qs[i].l, qs[i].r);
    }

    return 0;
}
