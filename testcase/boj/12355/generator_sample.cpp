#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> increasingCase(int n) {
    vector<int> a(n);
    int cur = rnd.next(1, 20);
    for (int i = 0; i < n; ++i) {
        cur += rnd.next(1, 8);
        a[i] = min(cur, 1000);
    }
    return a;
}

vector<int> decreasingCase(int n) {
    vector<int> a = increasingCase(n);
    reverse(a.begin(), a.end());
    return a;
}

vector<int> plateauCase(int n) {
    vector<int> a(n);
    int blocks = rnd.next(1, min(n, 6));
    vector<int> values;
    for (int i = 0; i < blocks; ++i) values.push_back(rnd.next(1, 1000));
    sort(values.begin(), values.end());

    for (int i = 0; i < n; ++i) {
        int block = min(blocks - 1, i * blocks / n);
        a[i] = values[block];
    }
    if (rnd.next(2)) reverse(a.begin(), a.end());
    return a;
}

vector<int> sawCase(int n) {
    vector<int> a(n);
    int low = rnd.next(1, 30);
    int high = rnd.next(900, 1000);
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            a[i] = rnd.next(low, min(1000, low + 80));
        } else {
            a[i] = rnd.next(max(1, high - 80), high);
        }
    }
    return a;
}

vector<int> randomCase(int n) {
    vector<int> a(n);
    int lo = rnd.next(1, 700);
    int hi = rnd.next(lo, 1000);
    for (int& x : a) x = rnd.next(lo, hi);
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(5);
        int n = rnd.next(1, 30);
        if (rnd.next(8) == 0) n = rnd.next(31, 80);

        vector<int> a;
        if (mode == 0) {
            a = increasingCase(n);
        } else if (mode == 1) {
            a = decreasingCase(n);
        } else if (mode == 2) {
            a = plateauCase(n);
        } else if (mode == 3) {
            a = sawCase(n);
        } else {
            a = randomCase(n);
        }

        println(n);
        println(a);
    }

    return 0;
}
