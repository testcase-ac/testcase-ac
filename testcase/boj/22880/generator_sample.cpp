#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

static vector<int> increasing(int n) {
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    return a;
}

static vector<int> decreasing(int n) {
    vector<int> a = increasing(n);
    reverse(a.begin(), a.end());
    return a;
}

static vector<int> randomPermutation(int n) {
    vector<int> a = increasing(n);
    shuffle(a.begin(), a.end());
    return a;
}

static vector<int> recordBlocks(int n) {
    vector<int> a;
    int nextLow = 1;
    int nextHigh = n;

    while ((int)a.size() < n) {
        a.push_back(nextHigh--);
        int remaining = n - (int)a.size();
        int tail = rnd.next(0, min(remaining, 5));
        vector<int> block;
        for (int i = 0; i < tail; ++i) block.push_back(nextLow++);
        shuffle(block.begin(), block.end());
        a.insert(a.end(), block.begin(), block.end());
    }

    return a;
}

static vector<int> localSwaps(int n) {
    vector<int> a = increasing(n);
    int swaps = rnd.next(1, max(1, n / 2));
    for (int i = 0; i < swaps; ++i) {
        int p = rnd.next(0, n - 1);
        int q = rnd.next(max(0, p - 2), min(n - 1, p + 2));
        swap(a[p], a[q]);
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 80);
    int mode = rnd.next(0, 5);

    vector<int> heights;
    if (mode == 0) {
        heights = increasing(n);
    } else if (mode == 1) {
        heights = decreasing(n);
    } else if (mode == 2) {
        heights = randomPermutation(n);
    } else if (mode == 3) {
        heights = recordBlocks(n);
    } else {
        heights = localSwaps(n);
    }

    println(n);
    println(heights);
    return 0;
}
