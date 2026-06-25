#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_A = 1000000000;
const int MASK_30 = (1 << 30) - 1;

int clampValue(long long x) {
    if (x < 1) return 1;
    if (x > MAX_A) return MAX_A;
    return (int)x;
}

vector<int> randomArray(int n, int lo, int hi) {
    vector<int> a(n);
    for (int &x : a) x = rnd.next(lo, hi);
    return a;
}

void printCase(const vector<int> &c, const vector<int> &d) {
    println((int)c.size());
    println(c);
    println(d);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> c, d;

    if (mode == 0) {
        n = rnd.next(1, 8);
        int hi = rnd.next(1, 32);
        c = randomArray(n, 1, hi);
        d = randomArray(n, 1, hi);
    } else if (mode == 1) {
        n = rnd.next(2, 24);
        int baseC = rnd.next(1, MAX_A);
        int baseD = rnd.next(1, MAX_A);
        c.assign(n, baseC);
        d.assign(n, baseD);
        int changes = rnd.next(1, n);
        for (int i = 0; i < changes; ++i) {
            c[rnd.next(n)] = clampValue((long long)baseC + rnd.next(-3, 3));
            d[rnd.next(n)] = clampValue((long long)baseD + rnd.next(-3, 3));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        int bit = rnd.next(1, 29);
        int pivot = 1 << bit;
        for (int i = 0; i < n; ++i) {
            int deltaC = rnd.next(-8, 8);
            int deltaD = rnd.next(-8, 8);
            c.push_back(clampValue((long long)pivot + deltaC));
            d.push_back(clampValue((long long)(pivot - 1) + deltaD));
        }
        shuffle(c.begin(), c.end());
        shuffle(d.begin(), d.end());
    } else if (mode == 3) {
        n = rnd.next(2, 28);
        int mask = rnd.next(1, MASK_30);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(1, MAX_A);
            int y = (x ^ mask) & MASK_30;
            if (y == 0 || y > MAX_A) y = rnd.next(1, MAX_A);
            c.push_back(x);
            d.push_back(y);
        }
        shuffle(d.begin(), d.end());
    } else if (mode == 4) {
        n = rnd.next(20, 100);
        int lo = rnd.next(1, MAX_A - 2000);
        int hi = lo + rnd.next(0, 2000);
        c = randomArray(n, lo, hi);
        d = randomArray(n, lo, hi);
    } else {
        n = 100;
        c = randomArray(n, 1, MAX_A);
        d = randomArray(n, 1, MAX_A);
        c[rnd.next(n)] = 1;
        d[rnd.next(n)] = MAX_A;
    }

    printCase(c, d);
    return 0;
}
