#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> randomBuckets(int lo, int hi) {
    vector<int> buckets(10);
    for (int& x : buckets) x = rnd.next(lo, hi);
    return buckets;
}

void printCase(const vector<int>& first, const vector<int>& second) {
    println(first);
    println(second);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    vector<int> first;
    vector<int> second;

    if (mode == 0) {
        int value = rnd.next(1, 100);
        first.assign(10, value);
        second.assign(10, value);
    } else if (mode == 1) {
        int a = rnd.next(1, 100);
        int b = rnd.next(1, 100);
        first.assign(10, a);
        second.assign(10, b);
    } else if (mode == 2) {
        int lo = rnd.next(1, 90);
        int hi = min(100, lo + rnd.next(0, 10));
        first = randomBuckets(lo, hi);
        second = randomBuckets(lo, hi);
    } else if (mode == 3) {
        first = randomBuckets(1, 15);
        second = randomBuckets(85, 100);
        if (rnd.next(0, 1)) swap(first, second);
    } else if (mode == 4) {
        first = randomBuckets(1, 100);
        second = first;
        shuffle(second.begin(), second.end());
        int changes = rnd.next(1, 4);
        for (int i = 0; i < changes; ++i) second[rnd.next(0, 9)] = rnd.next(1, 100);
    } else if (mode == 5) {
        vector<int> pool;
        int poolSize = rnd.next(2, 6);
        for (int i = 0; i < poolSize; ++i) pool.push_back(rnd.next(1, 100));
        for (int i = 0; i < 10; ++i) {
            first.push_back(rnd.any(pool));
            second.push_back(rnd.any(pool));
        }
    } else if (mode == 6) {
        first = {1, 1, 2, 2, 3, 5, 8, 13, 21, 34};
        second = {55, 55, 56, 56, 57, 58, 60, 70, 90, 100};
        shuffle(first.begin(), first.end());
        shuffle(second.begin(), second.end());
    } else {
        first.clear();
        second.clear();
        for (int i = 0; i < 10; ++i) {
            first.push_back(i % 2 == 0 ? 1 : 100);
            second.push_back(rnd.next(1, 100));
        }
        shuffle(first.begin(), first.end());
        shuffle(second.begin(), second.end());
    }

    printCase(first, second);
    return 0;
}
