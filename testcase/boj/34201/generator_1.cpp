#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n;
    if (sizeMode == 0) n = 1;
    else if (sizeMode == 1) n = rnd.next(2, 5);
    else if (sizeMode == 2) n = rnd.next(6, 15);
    else if (sizeMode == 3) n = rnd.next(16, 40);
    else n = rnd.next(41, 100);

    long long s = rnd.next(-1000000, 1000000);
    vector<long long> a;
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        long long v = rnd.next(-100, 100);
        a.assign(n, v);
    } else if (mode == 1) {
        long long cur = rnd.next(-1000, 1000);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 5);
            a.push_back(cur);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(-50, 50));
        }
        sort(a.begin(), a.end());
    } else if (mode == 3) {
        a.push_back(-1000000000LL);
        while ((int)a.size() < n) {
            a.push_back(rnd.next(-1000000, 1000000));
        }
        sort(a.begin(), a.end());
    } else {
        a.push_back(1000000000LL);
        while ((int)a.size() < n) {
            a.push_back(rnd.next(-1000000, 1000000));
        }
        sort(a.begin(), a.end());
    }

    println(n, s);
    println(a);
    return 0;
}
