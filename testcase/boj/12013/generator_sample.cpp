#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

vector<int> mergeableBlock(int value, int depth) {
    if (depth == 0) return {value};

    vector<int> left = mergeableBlock(value, depth - 1);
    vector<int> right = mergeableBlock(value, depth - 1);
    left.insert(left.end(), right.begin(), right.end());
    return left;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> a;
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        int depth = rnd.next(1, 5);
        int base = rnd.next(1, 40);
        a = mergeableBlock(base, depth);
    } else if (mode == 1) {
        int depth = rnd.next(1, 4);
        int base = rnd.next(1, 36);
        a = mergeableBlock(base, depth);
        int extras = rnd.next(1, 8);
        for (int i = 0; i < extras; ++i) {
            int value = rnd.next(max(1, base - 2), min(40, base + 4));
            if (rnd.next(0, 1)) {
                a.insert(a.begin() + rnd.next((int)a.size() + 1), value);
            } else {
                a.push_back(value);
            }
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 30);
        int first = rnd.next(1, 39);
        for (int i = 0; i < n; ++i) a.push_back(first + (i % 2));
    } else if (mode == 3) {
        int pairs = rnd.next(1, 12);
        int lo = rnd.next(1, 38);
        int hi = rnd.next(lo, min(40, lo + rnd.next(0, 5)));
        for (int i = 0; i < pairs; ++i) {
            int value = rnd.next(lo, hi);
            a.push_back(value);
            a.push_back(value);
        }
        if (rnd.next(0, 1)) shuffle(a.begin(), a.end());
    } else {
        int n = rnd.next(2, 35);
        int lo = rnd.next(1, 38);
        int hi = rnd.next(lo, min(40, lo + rnd.next(0, 8)));
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    }

    while ((int)a.size() < 2) a.push_back(rnd.next(1, 40));
    if ((int)a.size() > 248) a.resize(248);

    println((int)a.size());
    for (int value : a) println(value);

    return 0;
}
