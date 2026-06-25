#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int remainingSum(const vector<int>& a) {
    return 10000 - accumulate(a.begin(), a.end(), 0);
}

void appendPositiveParts(vector<int>& a, int count, int total, int maxPart) {
    for (int i = 0; i < count; ++i) {
        int remainingCount = count - i - 1;
        int hi = min(maxPart, total - remainingCount);
        int value = rnd.next(1, hi);
        a.push_back(value);
        total -= value;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> a;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        a.push_back(rnd.next(1, 10000));
    } else if (mode == 1) {
        int n = rnd.next(2, 120);
        int value = rnd.next(1, max(1, 10000 / n));
        a.assign(n, value);
    } else if (mode == 2) {
        int n = rnd.next(2, 80);
        appendPositiveParts(a, n, rnd.next(n, min(10000, n * 40)), 200);
    } else if (mode == 3) {
        int pairCount = rnd.next(1, 40);
        for (int i = 0; i < pairCount; ++i) {
            int value = rnd.next(1, max(1, remainingSum(a) / (2 * (pairCount - i))));
            a.push_back(value);
            a.push_back(value);
        }
    } else if (mode == 4) {
        int n = rnd.next(2, 30);
        int total = rnd.next(max(n, 9000), 10000);
        appendPositiveParts(a, n - 1, total - 1, 900);
        a.push_back(total - accumulate(a.begin(), a.end(), 0));
    } else if (mode == 5) {
        int n = rnd.next(10, 180);
        int total = rnd.next(n, min(10000, n * 12));
        appendPositiveParts(a, n, total, 25);
    } else {
        int n = rnd.next(2, 1000);
        a.assign(n, 1);
    }

    shuffle(a.begin(), a.end());
    println(static_cast<int>(a.size()));
    println(a);

    return 0;
}
