#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int LIM = 1000000000;

int edgeValue() {
    return rnd.any(vector<int>{-LIM, -LIM + 1, -100, -1, 0, 1, 100, LIM - 1, LIM});
}

vector<int> consecutiveRun() {
    int n = rnd.next(2, 12);
    int start = rnd.next(-30, 30);
    vector<int> a;
    for (int i = 0; i < n; ++i) {
        int copies = rnd.next(1, 3);
        for (int j = 0; j < copies && (int)a.size() < n; ++j) {
            a.push_back(start + i);
        }
    }
    return a;
}

vector<int> duplicateBlocks() {
    int blocks = rnd.next(2, 7);
    int start = rnd.next(-40, 40);
    int step = rnd.next(2, 8);
    vector<int> a;
    for (int i = 0; i < blocks; ++i) {
        int value = start + i * step;
        int copies = rnd.next(1, 5);
        for (int j = 0; j < copies; ++j) {
            a.push_back(value);
        }
    }
    return a;
}

vector<int> nearConsecutiveGroups() {
    int groups = rnd.next(2, 5);
    int start = rnd.next(-25, 25);
    vector<int> a;
    for (int g = 0; g < groups; ++g) {
        int base = start + g * rnd.next(3, 8);
        a.push_back(base);
        a.push_back(base + 1);
        if (rnd.next(0, 1)) a.push_back(base + 1);
        if (rnd.next(0, 2) == 0) a.push_back(base + 2);
    }
    return a;
}

vector<int> randomSmallValues() {
    int n = rnd.next(1, 18);
    int lo = rnd.next(-20, 10);
    int hi = rnd.next(max(lo, -10), 30);
    vector<int> a;
    for (int i = 0; i < n; ++i) {
        a.push_back(rnd.next(lo, hi));
    }
    return a;
}

vector<int> boundaryValues() {
    int n = rnd.next(3, 12);
    vector<int> a;
    for (int i = 0; i < n; ++i) {
        if (rnd.next(0, 2) == 0) {
            a.push_back(edgeValue());
        } else {
            int base = rnd.any(vector<int>{-LIM, -LIM + 10, LIM - 10, LIM});
            int delta = rnd.next(-3, 3);
            long long value = 1LL * base + delta;
            value = max(-1000000000LL, min(1000000000LL, value));
            a.push_back((int)value);
        }
    }
    return a;
}

vector<int> makeCase(int mode) {
    if (mode == 0) return vector<int>{rnd.next(-5, 5)};
    if (mode == 1) return consecutiveRun();
    if (mode == 2) return duplicateBlocks();
    if (mode == 3) return nearConsecutiveGroups();
    if (mode == 4) return boundaryValues();
    return randomSmallValues();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(4, 10);
    for (int tc = 0; tc < datasets; ++tc) {
        int mode = tc < 6 ? tc : rnd.next(0, 5);
        vector<int> a = makeCase(mode);
        shuffle(a.begin(), a.end());

        println((int)a.size());
        println(a);
    }

    println(0);
    return 0;
}
