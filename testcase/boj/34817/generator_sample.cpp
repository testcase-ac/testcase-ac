#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, mode == 6 ? 30 : 12);
    int k;
    vector<int> a;

    if (mode == 0) {
        k = rnd.next(0, 5);
        int cur = rnd.next(0, 10);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 4);
            a.push_back(cur);
        }
    } else if (mode == 1) {
        k = rnd.next(0, 5);
        int base = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(base + rnd.next(0, k));
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        k = rnd.next(0, 8);
        int high = rnd.next(k + 1, k + 30);
        int low = rnd.next(0, high - k - 1);
        a.push_back(high);
        a.push_back(low);
        while ((int)a.size() < n) {
            a.push_back(rnd.next(0, high + 5));
        }
        shuffle(a.begin() + 2, a.end());
    } else if (mode == 3) {
        k = 0;
        int base = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(base + rnd.next(0, 4));
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        k = 1000000000;
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, 1000000000));
        }
    } else if (mode == 5) {
        k = rnd.next(1, 10);
        int cur = rnd.next(0, 30);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(-k, k);
            cur = max(0, cur);
            a.push_back(cur);
        }
    } else {
        n = rnd.next(15, 30);
        k = rnd.next(0, 1000000000);
        for (int i = 0; i < n; ++i) {
            if (i % 7 == 0) {
                a.push_back(rnd.next(900000000, 1000000000));
            } else {
                a.push_back(rnd.next(0, 100000000));
            }
        }
    }

    println(n, k);
    for (int i = 0; i < n; ++i) {
        if (i) {
            printf(" ");
        }
        printf("%d", a[i]);
    }
    printf("\n");

    return 0;
}
