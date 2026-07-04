#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int clampValue(int x) {
    return max(1, min(999, x));
}

vector<int> makeTrapList(int n) {
    vector<int> values;
    values.reserve(n);

    int low = rnd.next(1, 30);
    int high = rnd.next(850, 999);
    int mid = rnd.next(300, 700);

    while ((int)values.size() < n) {
        int block = rnd.next(0, 3);
        if (block == 0) {
            values.push_back(high);
            if ((int)values.size() < n) values.push_back(low);
        } else if (block == 1) {
            int len = rnd.next(1, min(4, n - (int)values.size()));
            for (int i = 0; i < len; ++i) values.push_back(clampValue(mid + rnd.next(-12, 12)));
        } else if (block == 2) {
            int len = rnd.next(1, min(3, n - (int)values.size()));
            for (int i = 0; i < len; ++i) values.push_back(clampValue(low + rnd.next(0, 20)));
        } else {
            int len = rnd.next(1, min(3, n - (int)values.size()));
            for (int i = 0; i < len; ++i) values.push_back(clampValue(high - rnd.next(0, 20)));
        }
    }

    return values;
}

vector<int> makeList(int n, int mode) {
    vector<int> values(n);

    if (mode == 0) {
        int x = rnd.next(1, 999);
        fill(values.begin(), values.end(), x);
    } else if (mode == 1) {
        int lo = rnd.next(1, 50);
        int hi = rnd.next(950, 999);
        for (int i = 0; i < n; ++i) values[i] = (i % 2 == 0 ? lo : hi);
    } else if (mode == 2) {
        int start = rnd.next(1, 999);
        int step = rnd.next(-12, 12);
        if (step == 0) step = 1;
        for (int i = 0; i < n; ++i) {
            values[i] = clampValue(start + i * step + rnd.next(-2, 2));
        }
    } else if (mode == 3) {
        int clusters = rnd.next(2, min(6, n));
        vector<int> centers;
        for (int i = 0; i < clusters; ++i) centers.push_back(rnd.next(1, 999));
        for (int i = 0; i < n; ++i) {
            int center = rnd.any(centers);
            values[i] = clampValue(center + rnd.next(-8, 8));
        }
    } else if (mode == 4) {
        int lo = rnd.next(1, 800);
        int hi = rnd.next(lo, 999);
        for (int i = 0; i < n; ++i) values[i] = rnd.next(lo, hi);
    } else if (mode == 5) {
        values = makeTrapList(n);
    } else {
        for (int& value : values) value = rnd.next(1, 999);
    }

    if (rnd.next(0, 1) == 1) reverse(values.begin(), values.end());
    return values;
}

int chooseK(int n, int mode) {
    if (n == 1) return 1;
    if (mode == 0) return 1;
    if (mode == 1) return n;
    if (mode == 2) return rnd.next(1, min(n, 4));
    if (mode == 3) return rnd.next(max(1, n - 3), n);
    if (mode == 5) return rnd.next(2, min(n, 8));
    return rnd.next(1, n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tc = rnd.next(4, 10);
    println(tc);

    for (int t = 0; t < tc; ++t) {
        int mode = rnd.next(0, 6);
        int n;
        if (mode == 0) {
            n = 1;
        } else if (mode <= 3) {
            n = rnd.next(2, 12);
        } else if (mode == 5) {
            n = rnd.next(8, 28);
        } else {
            n = rnd.next(13, 30);
        }

        int k = chooseK(n, mode);
        vector<int> values = makeList(n, mode);

        printf("\n");
        println(n, k);
        println(values);
    }

    return 0;
}
