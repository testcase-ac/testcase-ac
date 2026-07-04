#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

const int SCALE = 10000;

struct CaseData {
    int n;
    int k;
    int u;
    vector<int> p;
};

string fixed4(int value) {
    return toString(value / SCALE) + "." + format("%04d", value % SCALE);
}

int capacity(const vector<int>& p) {
    return static_cast<int>(1LL * p.size() * SCALE - accumulate(p.begin(), p.end(), 0LL));
}

vector<int> randomProbabilities(int n, int mode) {
    vector<int> p(n);

    if (mode == 0) {
        fill(p.begin(), p.end(), 0);
    } else if (mode == 1) {
        fill(p.begin(), p.end(), SCALE);
    } else if (mode == 2) {
        int base = rnd.next(2500, 7500);
        for (int& x : p) {
            x = max(0, min(SCALE, base + rnd.next(-600, 600)));
        }
    } else if (mode == 3) {
        for (int& x : p) {
            x = rnd.any(vector<int>{0, 1, 100, 9999, SCALE, rnd.next(0, SCALE)});
        }
    } else if (mode == 4) {
        int lo = rnd.next(0, 4000);
        int hi = rnd.next(max(lo, 6000), SCALE);
        for (int& x : p) {
            x = rnd.next(lo, hi);
        }
    } else {
        for (int& x : p) {
            x = rnd.next(0, SCALE);
        }
    }

    shuffle(p.begin(), p.end());
    return p;
}

CaseData makeCase(int mode) {
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else if (mode == 2) {
        n = rnd.next(6, 14);
    } else if (mode == 3) {
        n = rnd.next(15, 30);
    } else if (mode == 4) {
        n = rnd.next(40, 50);
    } else {
        n = rnd.next(1, 50);
    }

    int probMode = rnd.next(0, 5);
    if (mode == 0) probMode = rnd.next(0, 3);
    if (mode == 4) probMode = rnd.any(vector<int>{0, 2, 3, 5});

    vector<int> p = randomProbabilities(n, probMode);
    int freeUnits = capacity(p);

    int u;
    int uMode = rnd.next(0, 5);
    if (freeUnits == 0 || uMode == 0) {
        u = 0;
    } else if (uMode == 1) {
        u = freeUnits;
    } else if (uMode == 2) {
        u = rnd.next(0, min(freeUnits, SCALE));
    } else if (uMode == 3) {
        u = rnd.next(max(0, freeUnits - SCALE), freeUnits);
    } else {
        u = rnd.next(0, freeUnits);
    }

    int k;
    if (mode == 0) {
        k = 1;
    } else {
        k = rnd.any(vector<int>{1, n, rnd.next(1, n), rnd.next(1, n)});
    }

    return {n, k, u, p};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 18);
    vector<CaseData> cases;
    cases.reserve(t);

    cases.push_back({1, 1, 0, {0}});
    cases.push_back({2, 2, SCALE, {0, 0}});
    cases.push_back({2, 1, 0, {9000, 8000}});
    cases.push_back({4, 4, 14000, {5000, 7000, 8000, 6000}});
    cases.push_back({50, rnd.next(1, 50), 0, vector<int>(50, SCALE)});

    while (static_cast<int>(cases.size()) < t) {
        cases.push_back(makeCase(rnd.next(0, 5)));
    }

    shuffle(cases.begin(), cases.end());

    println(static_cast<int>(cases.size()));
    for (const CaseData& c : cases) {
        println(c.n, c.k);
        println(fixed4(c.u));
        vector<string> probabilities;
        probabilities.reserve(c.p.size());
        for (int x : c.p) {
            probabilities.push_back(fixed4(x));
        }
        println(probabilities);
    }

    return 0;
}
