#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 14);
    int m = rnd.next(1, 14);
    vector<int> a(n), b(m);

    if (mode == 0) {
        int base = rnd.next(0, 20);
        for (int& x : a) x = rnd.next(base + 10, base + 80);
        for (int& x : b) x = rnd.next(base, base + 20);
    } else if (mode == 1) {
        int base = rnd.next(20, 90);
        for (int& x : a) x = rnd.next(0, base - 1);
        for (int& x : b) x = rnd.next(base, base + 60);
    } else if (mode == 2) {
        int pivot = rnd.next(0, 100);
        for (int& x : a) x = max(0, pivot + rnd.next(-15, 25));
        for (int& x : b) x = max(0, pivot + rnd.next(-25, 15));
    } else if (mode == 3) {
        vector<int> vals = {0, 1, rnd.next(2, 8), rnd.next(9, 30), 1000000000};
        for (int& x : a) x = rnd.any(vals);
        for (int& x : b) x = rnd.any(vals);
    } else if (mode == 4) {
        n = rnd.next(1, 3);
        m = rnd.next(8, 14);
        a.assign(n, 0);
        b.assign(m, 0);
        int cap = rnd.next(0, 100);
        for (int& x : a) x = rnd.next(0, cap);
        for (int& x : b) x = rnd.next(0, cap + 20);
    } else if (mode == 5) {
        n = rnd.next(8, 14);
        m = rnd.next(1, 3);
        a.assign(n, 0);
        b.assign(m, 0);
        int cap = rnd.next(0, 100);
        for (int& x : a) x = rnd.next(0, cap + 20);
        for (int& x : b) x = rnd.next(0, cap);
    } else {
        for (int& x : a) x = rnd.next(0, 1000000000);
        for (int& x : b) x = rnd.next(0, 1000000000);
    }

    if (rnd.next(0, 3) == 0) {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end(), greater<int>());
    } else {
        shuffle(a.begin(), a.end());
        shuffle(b.begin(), b.end());
    }

    println(n, m);
    println(a);
    println(b);

    return 0;
}
