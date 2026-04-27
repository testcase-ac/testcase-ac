#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 5);
    int n;
    if (sizeMode == 0) n = 1;
    else if (sizeMode == 1) n = rnd.next(2, 5);
    else if (sizeMode == 2) n = rnd.next(6, 15);
    else if (sizeMode == 3) n = rnd.next(16, 40);
    else if (sizeMode == 4) n = rnd.next(41, 90);
    else n = rnd.next(91, 150);

    int kMode = rnd.next(0, 4);
    int k;
    if (kMode == 0) k = 1;
    else if (kMode == 1) k = n;
    else if (kMode == 2) k = (n + 1) / 2;
    else k = rnd.next(1, n);

    int cMode = rnd.next(0, 5);
    int c;
    if (cMode == 0) c = 1;
    else if (cMode == 1) c = rnd.next(2, 10);
    else if (cMode == 2) c = rnd.next(11, 80);
    else if (cMode == 3) c = rnd.next(81, 300);
    else if (cMode == 4) c = rnd.next(301, 1000);
    else c = rnd.next(1001, 5000);

    vector<int> a(n);
    int valueMode = rnd.next(0, 6);
    if (valueMode == 0) {
        int x = rnd.next(1, 30);
        fill(a.begin(), a.end(), x);
    } else if (valueMode == 1) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, 20);
    } else if (valueMode == 2) {
        int cur = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 4);
            a[i] = cur;
        }
    } else if (valueMode == 3) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) a[i] = rnd.next(1, 10);
            else a[i] = rnd.next(80, 250);
        }
    } else if (valueMode == 4) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1, c + 20);
    } else if (valueMode == 5) {
        for (int i = 0; i < n; ++i) {
            int base = rnd.next(0, 5) == 0 ? 1000000 : rnd.next(999000, 1000000);
            a[i] = base;
        }
    } else {
        int first = rnd.next(1, 50);
        int second = rnd.next(51, 200);
        for (int i = 0; i < n; ++i) a[i] = (rnd.next(0, 1) ? first : second);
    }

    int orderMode = rnd.next(0, 3);
    if (orderMode == 0) {
        sort(a.begin(), a.end());
    } else if (orderMode == 1) {
        sort(a.rbegin(), a.rend());
    } else if (orderMode == 2) {
        shuffle(a.begin(), a.end());
    }

    println(n, k, c);
    println(a);
    return 0;
}
