#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct CaseData {
    int n;
    int e;
    vector<int> sizes;
};

int sumSizes(const vector<int>& sizes) {
    return accumulate(sizes.begin(), sizes.end(), 0);
}

CaseData makeCase(int mode) {
    int n;
    vector<int> sizes;

    if (mode == 0) {
        n = rnd.next(1, 12);
        sizes.resize(n);
        for (int& size : sizes) size = rnd.next(1, 40);
        return {n, 0, sizes};
    }

    if (mode == 1) {
        n = rnd.next(2, 16);
        sizes.resize(n);
        for (int& size : sizes) size = rnd.next(1, 80);
        shuffle(sizes.begin(), sizes.end());
        int picked = rnd.next(1, n);
        int need = 0;
        for (int i = 0; i < picked; ++i) need += sizes[i];
        shuffle(sizes.begin(), sizes.end());
        return {n, 2 * need, sizes};
    }

    if (mode == 2) {
        n = rnd.next(1, 20);
        sizes.resize(n);
        for (int& size : sizes) size = rnd.next(1, 60);
        int total = sumSizes(sizes);
        int e = 2 * total + rnd.next(1, 200);
        return {n, e, sizes};
    }

    if (mode == 3) {
        n = rnd.next(10, 30);
        int base = rnd.next(1, 40);
        sizes.resize(n);
        for (int i = 0; i < n; ++i) sizes[i] = base + rnd.next(0, 3);
        int total = sumSizes(sizes);
        int e = rnd.next(1, 2 * total);
        shuffle(sizes.begin(), sizes.end());
        return {n, e, sizes};
    }

    if (mode == 4) {
        n = rnd.next(8, 25);
        sizes.resize(n);
        int value = 1;
        for (int i = 0; i < n; ++i) {
            value += rnd.next(0, 7);
            sizes[i] = min(value, 2000);
        }
        int total = sumSizes(sizes);
        int e = rnd.next(max(1, total - 20), min(2 * total, total + 120));
        shuffle(sizes.begin(), sizes.end());
        return {n, e, sizes};
    }

    if (mode == 5) {
        n = rnd.next(6, 18);
        sizes.resize(n);
        for (int& size : sizes) size = rnd.next(1500, 2000);
        int total = sumSizes(sizes);
        int e = rnd.next(1, min(1000000000, 2 * total + 5000));
        return {n, e, sizes};
    }

    n = rnd.next(70, 100);
    sizes.resize(n);
    for (int i = 0; i < n; ++i) {
        if (rnd.next(100) < 70) {
            sizes[i] = rnd.next(1, 25);
        } else {
            sizes[i] = rnd.next(500, 2000);
        }
    }
    int total = sumSizes(sizes);
    int e = rnd.next(1, min(1000000000, 2 * total + 1000));
    shuffle(sizes.begin(), sizes.end());
    return {n, e, sizes};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 18);
    println(t);

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        CaseData data = makeCase(rnd.next(0, 6));
        println(data.n, data.e);
        println(data.sizes);
    }

    return 0;
}
