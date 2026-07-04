#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MIN_VALUE = 1;
const int MAX_VALUE = 1000000;

vector<int> shuffledValues(int count, int lo, int hi) {
    vector<int> values;
    for (int i = 0; i < count; ++i) values.push_back(rnd.next(lo, hi));
    shuffle(values.begin(), values.end());
    return values;
}

vector<int> repeatedBlocks(int n, const vector<int>& blockValues) {
    vector<int> values;
    for (int value : blockValues) {
        for (int i = 0; i < n; ++i) values.push_back(value);
    }
    shuffle(values.begin(), values.end());
    return values;
}

vector<int> arithmeticValues(int count, int start, int step) {
    vector<int> values;
    for (int i = 0; i < count; ++i) values.push_back(start + i * step);
    shuffle(values.begin(), values.end());
    return values;
}

int clamped(int value) {
    return min(MAX_VALUE, max(MIN_VALUE, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCases = rnd.next(4, 10);
    println(testCases);

    for (int tc = 0; tc < testCases; ++tc) {
        int n = rnd.next(3, 5);
        int count = 3 * n;
        int mode = rnd.next(0, 6);

        vector<int> a;
        vector<int> b;

        if (mode == 0) {
            int base = rnd.next(1, 20);
            a = repeatedBlocks(n, {base, base, base + rnd.next(0, 2)});
            b = repeatedBlocks(n, {base, base, base});
        } else if (mode == 1) {
            int base = rnd.next(2, 80);
            int delta = rnd.next(0, 3);
            a = shuffledValues(count, base, base + delta);
            b = shuffledValues(count, base, base + delta);
        } else if (mode == 2) {
            int low = rnd.next(1, 30);
            int high = rnd.next(999970, MAX_VALUE);
            a = repeatedBlocks(n, {high, low, low + rnd.next(0, 5)});
            b = repeatedBlocks(n, {low, high, high - rnd.next(0, 5)});
        } else if (mode == 3) {
            int start = rnd.next(1, 100);
            int step = rnd.next(1, 11);
            a = arithmeticValues(count, start, step);
            b = arithmeticValues(count, start + rnd.next(0, 4), step);
        } else if (mode == 4) {
            int base = rnd.next(200, 5000);
            a = shuffledValues(count, clamped(base - rnd.next(0, 20)),
                               clamped(base + rnd.next(0, 20)));
            b = shuffledValues(count, clamped(base - rnd.next(0, 20)),
                               clamped(base + rnd.next(0, 20)));
        } else if (mode == 5) {
            a = shuffledValues(count, 1, rnd.next(1, 50));
            b = shuffledValues(count, rnd.next(999950, MAX_VALUE), MAX_VALUE);
        } else {
            int base = rnd.next(10, 200);
            a = repeatedBlocks(n, {base + 3, base + 2, base + 1});
            b = repeatedBlocks(n, {base, base + 2, base + 4});
        }

        println(n);
        println(a);
        println(b);
    }

    return 0;
}
