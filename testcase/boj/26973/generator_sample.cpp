#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_A = 5000000;

int clampValue(int value) {
    return max(1, min(MAX_A, value));
}

int randomByResidue(int residue, int low, int high) {
    int first = low;
    while (first % 4 != residue) ++first;
    int last = high;
    while (last % 4 != residue) --last;
    if (first > last) return rnd.next(low, high);
    int count = (last - first) / 4 + 1;
    return first + 4 * rnd.next(count);
}

vector<int> makeCase(int mode) {
    if (mode == 0) {
        return {rnd.any(vector<int>{1, 2, 3, 4, 5, 8, 9, 12, 16, MAX_A})};
    }

    if (mode == 1) {
        int n = rnd.next(2, 8);
        vector<int> a;
        for (int i = 0; i < n; ++i) {
            int base = rnd.next(1, 8) * 4;
            int delta = rnd.any(vector<int>{-3, -2, -1, 0, 1, 2, 3});
            a.push_back(clampValue(base + delta));
        }
        return a;
    }

    if (mode == 2) {
        int n = rnd.next(2, 12);
        vector<int> pool = {1, 2, 3, 4, 7, 8, 9, 10, 15, 16, 17, 20, 24, 25};
        vector<int> a;
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
        return a;
    }

    if (mode == 3) {
        int n = rnd.next(3, 14);
        vector<int> a;
        int preferredResidue = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) {
            int residue = rnd.next(0, 99) < 70 ? preferredResidue : rnd.next(0, 3);
            a.push_back(randomByResidue(residue, 1, 200));
        }
        return a;
    }

    if (mode == 4) {
        int n = rnd.next(2, 10);
        vector<int> a;
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 35) {
                a.push_back(rnd.any(vector<int>{4999991, 4999993, 4999996, 4999999, MAX_A}));
            } else {
                a.push_back(rnd.next(1, 60));
            }
        }
        return a;
    }

    int n = rnd.next(1, 20);
    vector<int> a;
    int high = rnd.any(vector<int>{10, 30, 100, 1000, MAX_A});
    for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, high));
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 18);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        vector<int> a = makeCase(tc < 6 ? tc : rnd.next(0, 5));
        if (rnd.next(0, 1)) shuffle(a.begin(), a.end());

        println((int)a.size());
        println(a);
    }

    return 0;
}
