#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 5) {
        n = rnd.next(30, 80);
    } else {
        n = rnd.next(1, 20);
    }

    int k;
    if (rnd.next(4) == 0) {
        k = rnd.any(vector<int>{1, n});
    } else {
        k = rnd.next(1, n);
    }

    vector<int> a(n);
    if (mode == 0) {
        for (int& x : a) x = rnd.next(1, 30);
    } else if (mode == 1) {
        for (int& x : a) x = rnd.next(-30, -1);
    } else if (mode == 2) {
        for (int& x : a) x = rnd.next(-20, 20);
    } else if (mode == 3) {
        for (int& x : a) x = rnd.next(5) == 0 ? rnd.next(-100, 100) : 0;
    } else if (mode == 4) {
        vector<int> values = {-100000000, -1000, -1, 0, 1, 1000, 100000000};
        for (int& x : a) x = rnd.any(values);
    } else {
        int lo = rnd.next(-1000, 0);
        int hi = rnd.next(0, 1000);
        for (int& x : a) x = rnd.next(lo, hi);
    }

    println(n, k);
    println(a);

    return 0;
}
