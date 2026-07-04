#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

static vector<int> sortedUnique(vector<int> values) {
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    return values;
}

static vector<int> makeConsecutive(int n) {
    int start = rnd.next(1, 1000000 - n + 1);
    vector<int> a;
    for (int i = 0; i < n; ++i) a.push_back(start + i);
    return a;
}

static vector<int> makeArithmetic(int n) {
    int step = rnd.next(1, max(1, 1000000 / max(1, n - 1)));
    int maxStart = 1000000 - step * (n - 1);
    int start = rnd.next(1, maxStart);
    vector<int> a;
    for (int i = 0; i < n; ++i) a.push_back(start + step * i);
    return a;
}

static vector<int> makeClustered(int n) {
    int width = rnd.next(n - 1, min(200, n * 8));
    int base = rnd.next(1, 1000000 - width);
    set<int> chosen;
    while ((int)chosen.size() < n) chosen.insert(base + rnd.next(0, width));
    return vector<int>(chosen.begin(), chosen.end());
}

static vector<int> makeSparse(int n) {
    set<int> chosen;
    while ((int)chosen.size() < n) chosen.insert(rnd.next(1, 1000000));
    return vector<int>(chosen.begin(), chosen.end());
}

static vector<int> makeNearLimit(int n) {
    set<int> chosen;
    chosen.insert(1000000);
    int low = max(1, 1000000 - max(200, n * 20));
    while ((int)chosen.size() < n) chosen.insert(rnd.next(low, 1000000));
    return vector<int>(chosen.begin(), chosen.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 10);
    vector<vector<int>> tests;
    tests.push_back(vector<int>{rnd.next(1, 1000000)});

    while ((int)tests.size() < t) {
        int mode = rnd.next(0, 6);
        int n = rnd.next(2, 18);
        if (mode == 6) n = 100;

        vector<int> a;
        if (mode == 0) {
            a = makeConsecutive(n);
        } else if (mode == 1) {
            a = makeArithmetic(n);
        } else if (mode == 2) {
            a = makeClustered(n);
        } else if (mode == 3) {
            a = makeSparse(n);
        } else if (mode == 4) {
            a = makeNearLimit(n);
        } else if (mode == 5) {
            a = sortedUnique({1, 2, 3, 4, 5, 1000000});
            shuffle(a.begin(), a.end());
        } else {
            a = makeConsecutive(n);
            a.back() = 1000000;
        }

        shuffle(a.begin(), a.end());
        tests.push_back(a);
    }

    println((int)tests.size());
    for (const vector<int>& a : tests) {
        println((int)a.size());
        println(a);
    }

    return 0;
}
