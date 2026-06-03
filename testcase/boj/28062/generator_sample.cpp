#include "testlib.h"
#include <vector>
using namespace std;

int randomOdd(int lo, int hi) {
    int x = rnd.next(lo, hi);
    if (x % 2 == 0) {
        if (x < hi) ++x;
        else --x;
    }
    return x;
}

int randomEven(int lo, int hi) {
    int x = rnd.next(lo, hi);
    if (x % 2 == 1) {
        if (x < hi) ++x;
        else --x;
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 5) {
        n = rnd.next(50, 1000);
    } else {
        n = rnd.next(2, 25);
    }

    vector<int> a(n);
    if (mode == 0) {
        a[0] = rnd.next(0, 1) ? randomOdd(1, 999) : randomEven(2, 1000);
    } else if (mode == 1) {
        for (int& x : a) x = randomEven(2, 1000);
    } else if (mode == 2) {
        for (int& x : a) x = randomOdd(1, 999);
    } else if (mode == 3) {
        for (int& x : a) x = rnd.next(0, 1) ? randomOdd(1, 999) : randomEven(2, 1000);
    } else if (mode == 4) {
        for (int& x : a) x = rnd.any(vector<int>{1, 2, 3, 999, 1000});
    } else {
        for (int& x : a) x = rnd.next(1, 1000);
    }

    println(n);
    println(a);

    return 0;
}
