#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> randomMapping(int size, int limit) {
    vector<int> result(size);
    for (int& x : result) x = rnd.next(1, limit);
    return result;
}

vector<int> starMapping(int size, int limit) {
    int center = rnd.next(1, limit);
    vector<int> result(size, center);
    for (int& x : result) {
        if (rnd.next(0, 99) < 25) x = rnd.next(1, limit);
    }
    return result;
}

vector<int> cycleLikeMapping(int size, int limit) {
    vector<int> result(size);
    int offset = rnd.next(0, limit - 1);
    for (int i = 0; i < size; ++i) result[i] = (i + offset) % limit + 1;
    for (int& x : result) {
        if (rnd.next(0, 99) < 20) x = rnd.next(1, limit);
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int m;
    int n;
    if (mode == 0) {
        m = rnd.next(1, 4);
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        m = rnd.next(1, 3);
        n = rnd.next(8, 18);
    } else if (mode == 2) {
        m = rnd.next(8, 18);
        n = rnd.next(1, 3);
    } else {
        m = rnd.next(4, 16);
        n = rnd.next(4, 16);
    }

    vector<int> a;
    vector<int> b;
    if (mode == 3) {
        a = starMapping(m, n);
        b = starMapping(n, m);
    } else if (mode == 4) {
        a = cycleLikeMapping(m, n);
        b = cycleLikeMapping(n, m);
    } else {
        a = randomMapping(m, n);
        b = randomMapping(n, m);
    }

    if (rnd.next(0, 99) < 30) reverse(a.begin(), a.end());
    if (rnd.next(0, 99) < 30) reverse(b.begin(), b.end());

    println(m, n);
    println(a);
    println(b);
    return 0;
}
