#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long smallValue() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return rnd.next(-3, 3);
    if (mode == 1) return rnd.next(-20, 20);
    if (mode == 2) return rnd.any(vector<long long>{-1, 0, 1});
    if (mode == 3) return rnd.any(vector<long long>{-1000000000LL, -1000000LL, 1000000LL, 1000000000LL});
    return rnd.next(-1000, 1000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 20);
    if (mode == 6) n = rnd.next(21, 80);

    vector<long long> a;
    if (mode == 0) {
        for (int i = 0; i < n; ++i) a.push_back(smallValue());
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(-9, -1));
        int positives = rnd.next(0, min(n, 4));
        for (int i = 0; i < positives; ++i) a[i] = rnd.next(1, 9);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, 9));
        int nonPositive = rnd.next(0, min(n, 5));
        for (int i = 0; i < nonPositive; ++i) a[i] = rnd.any(vector<long long>{-2, -1, 0});
    } else if (mode == 3) {
        vector<long long> pool = {-1000000000LL, -999999999LL, -2, -1, 0, 1, 2, 999999999LL, 1000000000LL};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else if (mode == 4) {
        long long base = rnd.next(-7, 7);
        for (int i = 0; i < n; ++i) a.push_back(base + rnd.next(-2, 2));
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            long long v = rnd.next(-12, 12);
            if (rnd.next(0, 3) == 0) v = rnd.any(vector<long long>{-1, 0, 1});
            a.push_back(v);
        }
    } else {
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(-30, 30));
    }

    shuffle(a.begin(), a.end());
    println(n);
    println(a);
    return 0;
}
