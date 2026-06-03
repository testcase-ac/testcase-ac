#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 2000;
const int MAX_A = 1000000;

int chooseN(bool large) {
    if (large) return rnd.next(1200, MAX_N);
    int bucket = rnd.next(100);
    if (bucket < 15) return 1;
    if (bucket < 55) return rnd.next(2, 12);
    return rnd.next(13, 80);
}

int clampNote(int x) {
    return max(1, min(MAX_A, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    bool large = rnd.next(100) < 8;
    int n = chooseN(large);
    vector<int> a(n);

    if (mode == 0) {
        int value = rnd.next(1, MAX_A);
        fill(a.begin(), a.end(), value);
    } else if (mode == 1) {
        int lo = rnd.next(1, MAX_A - 2000);
        int step = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) a[i] = clampNote(lo + i * step);
        if (rnd.next(2)) reverse(a.begin(), a.end());
    } else if (mode == 2) {
        int low = rnd.next(1, 50);
        int high = rnd.next(MAX_A - 49, MAX_A);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? low : high);
    } else if (mode == 3) {
        int low = rnd.next(1, MAX_A / 2);
        int high = rnd.next(low, min(MAX_A, low + rnd.next(0, 200)));
        for (int i = 0; i < n; ++i) a[i] = rnd.next(low, high);
    } else if (mode == 4) {
        int cur = rnd.next(1, MAX_A);
        int maxStep = rnd.next(1, 5000);
        for (int i = 0; i < n; ++i) {
            cur = clampNote(cur + rnd.next(-maxStep, maxStep));
            a[i] = cur;
        }
    } else if (mode == 5) {
        vector<int> pool;
        int poolSize = rnd.next(2, 8);
        for (int i = 0; i < poolSize; ++i) pool.push_back(rnd.next(1, MAX_A));
        for (int i = 0; i < n; ++i) a[i] = rnd.any(pool);
    } else {
        int split = rnd.next(1, n);
        int first = rnd.next(1, MAX_A);
        int second = rnd.next(1, MAX_A);
        for (int i = 0; i < n; ++i) {
            int base = (i < split ? first : second);
            a[i] = clampNote(base + rnd.next(-20, 20));
        }
    }

    println(n);
    println(a);
    return 0;
}
