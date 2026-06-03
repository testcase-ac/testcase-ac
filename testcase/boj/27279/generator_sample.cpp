#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

vector<int> positiveComposition(int total, int parts) {
    vector<int> cuts;
    for (int i = 0; i < parts - 1; ++i) {
        cuts.push_back(rnd.next(1, total - 1));
    }
    cuts.push_back(0);
    cuts.push_back(total);
    sort(cuts.begin(), cuts.end());

    vector<int> result;
    for (int i = 1; i < (int)cuts.size(); ++i) {
        int piece = cuts[i] - cuts[i - 1];
        if (piece > 0) {
            result.push_back(piece);
        }
    }

    while ((int)result.size() < parts) {
        int idx = rnd.next((int)result.size());
        if (result[idx] == 1) {
            continue;
        }
        --result[idx];
        result.push_back(1);
    }
    while ((int)result.size() > parts) {
        int last = result.back();
        result.pop_back();
        result[rnd.next((int)result.size())] += last;
    }
    shuffle(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    int m;
    vector<int> a;
    vector<int> b;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, n);
        a.assign(n, rnd.next(1, m));
        b = positiveComposition(rnd.next(m, n), m);
    } else if (mode == 1) {
        n = rnd.next(5, 14);
        m = rnd.next(2, n);
        int lo = rnd.next(1, m);
        int hi = rnd.next(lo, m);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
        b = positiveComposition(rnd.next(m, n), m);
    } else if (mode == 2) {
        n = rnd.next(6, 16);
        m = rnd.next(2, min(n, 8));
        int total = rnd.next(max(m, n - 3), n);
        b = positiveComposition(total, m);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.wnext(m, rnd.next(-2, 3)) + 1);
        }
    } else if (mode == 3) {
        n = rnd.next(7, 18);
        m = rnd.next(3, min(n, 9));
        int weak = rnd.next(1, m);
        int strongCount = rnd.next(1, n);
        a.assign(n - strongCount, rnd.next(1, weak));
        for (int i = 0; i < strongCount; ++i) {
            a.push_back(rnd.next(weak, m));
        }
        b = positiveComposition(rnd.next(m, n), m);
    } else if (mode == 4) {
        n = rnd.next(10, 22);
        m = rnd.next(2, min(n, 10));
        for (int i = 0; i < n; ++i) {
            a.push_back((i % m) + 1);
        }
        b.assign(m, 1);
        int extra = rnd.next(0, n - m);
        while (extra-- > 0) {
            ++b[rnd.next(m)];
        }
    } else {
        n = rnd.next(20, 45);
        m = rnd.next(2, min(n, 12));
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 35) {
                a.push_back(rnd.any(vector<int>{1, m}));
            } else {
                a.push_back(rnd.next(1, m));
            }
        }
        b = positiveComposition(rnd.next(m, n), m);
    }

    shuffle(a.begin(), a.end());
    shuffle(b.begin(), b.end());

    println(n, m);
    println(a);
    println(b);

    return 0;
}
