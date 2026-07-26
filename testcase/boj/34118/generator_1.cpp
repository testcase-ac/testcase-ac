#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

string randomSchedule(int n, int percentOn) {
    string s(n, '0');
    for (int i = 0; i < n; ++i) {
        s[i] = rnd.next(0, 99) < percentOn ? '1' : '0';
    }
    return s;
}

string blockSchedule(int n, int blocks) {
    string s(n, '0');
    for (int k = 0; k < blocks; ++k) {
        int l = rnd.next(0, n - 1);
        int r = rnd.next(l, n - 1);
        for (int i = l; i <= r; ++i) {
            s[i] = '1';
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 5);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 6);
    } else if (sizeMode == 2) {
        n = rnd.next(7, 20);
    } else if (sizeMode == 3) {
        n = rnd.next(21, 80);
    } else if (sizeMode == 4) {
        n = rnd.next(100, 350);
    } else {
        n = rnd.next(1000, 2000);
    }

    string a(n, '0'), b(n, '0');
    int mode = rnd.next(0, 8);
    if (mode == 0) {
        a.assign(n, '1');
        b.assign(n, '1');
    } else if (mode == 1) {
        a = randomSchedule(n, rnd.next(20, 80));
        b.assign(n, '0');
    } else if (mode == 2) {
        a = randomSchedule(n, rnd.next(5, 35));
        b = randomSchedule(n, rnd.next(5, 35));
    } else if (mode == 3) {
        a = randomSchedule(n, rnd.next(65, 95));
        b = randomSchedule(n, rnd.next(65, 95));
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? '1' : '0');
            b[i] = (i % 2 == 1 ? '1' : '0');
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 3 != 0 ? '1' : '0');
            b[i] = (i % 4 != 0 ? '1' : '0');
        }
    } else if (mode == 6) {
        int blocks = rnd.next(1, min(n, 12));
        a = blockSchedule(n, blocks);
        b = blockSchedule(n, blocks);
    } else if (mode == 7) {
        int l = rnd.next(0, n - 1);
        int r = rnd.next(l, n - 1);
        for (int i = l; i <= r; ++i) {
            a[i] = '1';
        }
        int shift = rnd.next(-5, 5);
        for (int i = l; i <= r; ++i) {
            int j = i + shift;
            if (0 <= j && j < n) {
                b[j] = '1';
            }
        }
    } else {
        a = randomSchedule(n, 100);
        b = randomSchedule(n, rnd.next(0, 100));
    }

    int p1, p3, p5, ppair;
    int priceMode = rnd.next(0, 7);
    if (priceMode == 0) {
        p1 = 1;
        p3 = p5 = ppair = 10000;
    } else if (priceMode == 1) {
        ppair = 1;
        p1 = p3 = p5 = 10000;
    } else if (priceMode == 2) {
        p1 = rnd.next(1, 10);
        p3 = rnd.next(1, 10);
        p5 = rnd.next(1, 10);
        ppair = rnd.next(1, 10);
    } else if (priceMode == 3) {
        p1 = rnd.next(30, 100);
        p3 = rnd.next(1, 25);
        p5 = rnd.next(1, 25);
        ppair = rnd.next(1, 30);
    } else if (priceMode == 4) {
        p1 = rnd.next(1, 30);
        p3 = rnd.next(100, 300);
        p5 = rnd.next(1, 30);
        ppair = rnd.next(100, 300);
    } else if (priceMode == 5) {
        p1 = rnd.next(5000, 10000);
        p3 = rnd.next(1, 5000);
        p5 = rnd.next(1, 5000);
        ppair = rnd.next(1, 5000);
    } else if (priceMode == 6) {
        p1 = rnd.next(1, 10000);
        p3 = rnd.next(1, 10000);
        p5 = rnd.next(1, 10000);
        ppair = rnd.next(1, 10000);
    } else {
        p1 = rnd.any(vector<int>{1, 2, 9999, 10000});
        p3 = rnd.any(vector<int>{1, 3, 9998, 10000});
        p5 = rnd.any(vector<int>{1, 5, 9997, 10000});
        ppair = rnd.any(vector<int>{1, 4, 9996, 10000});
    }

    println(n);
    println(a);
    println(b);
    println(p1, p3, p5, ppair);
    return 0;
}
