#include "testlib.h"
#include <vector>

using namespace std;

const int MAX_A = 1000000;

int randomSubmask(int mask) {
    int value = 0;
    for (int bit = 0; bit < 20; ++bit) {
        if ((mask & (1 << bit)) && rnd.next(0, 1)) value |= 1 << bit;
    }
    return max(1, value);
}

int randomSupermask(int base) {
    int value = base;
    for (int bit = 0; bit < 20; ++bit) {
        if ((value & (1 << bit)) == 0 && rnd.next(0, 2) == 0) value |= 1 << bit;
    }
    if (value > MAX_A) value = MAX_A;
    return max(1, value);
}

vector<int> makeCase(int mode, int n) {
    vector<int> a;
    a.reserve(n);

    if (mode == 0) {
        int value = rnd.next(1, MAX_A);
        for (int i = 0; i < n; ++i) a.push_back(value);
    } else if (mode == 1) {
        int upper = rnd.next(2, 12);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, upper));
    } else if (mode == 2) {
        int mask = rnd.next(1, MAX_A);
        for (int i = 0; i < n; ++i) a.push_back(randomSubmask(mask));
    } else if (mode == 3) {
        int base = rnd.next(1, (1 << 10) - 1);
        for (int i = 0; i < n; ++i) a.push_back(randomSupermask(base));
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int bit = rnd.next(0, 19);
            int value = 1 << bit;
            if (value > MAX_A) value = MAX_A;
            a.push_back(value);
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            int value = MAX_A - rnd.next(0, 30);
            a.push_back(value);
        }
    } else {
        int lo = rnd.next(1, MAX_A);
        int hi = rnd.next(lo, MAX_A);
        if (hi - lo > 200) hi = lo + rnd.next(0, 200);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    }

    shuffle(a.begin(), a.end());
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int z = rnd.next(1, 10);
    println(z);

    for (int tc = 0; tc < z; ++tc) {
        int mode = rnd.next(0, 6);
        int n;
        if (rnd.next(0, 9) == 0) {
            n = rnd.next(30, 120);
        } else {
            n = rnd.next(1, 12);
        }

        vector<int> a = makeCase(mode, n);
        println(n);
        println(a);
    }

    return 0;
}
