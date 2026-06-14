#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const int MIN_VALUE = 1000000;
const int MAX_VALUE = 40000000;

int randomValue(int lo = MIN_VALUE, int hi = MAX_VALUE) {
    return rnd.next(lo, hi);
}

vector<int> makeCase(int mode) {
    vector<int> a;

    if (mode == 0) {
        a.push_back(randomValue());
    } else if (mode == 1) {
        int x = randomValue(MIN_VALUE, 20000000);
        int y = randomValue(MIN_VALUE, 20000000);
        a = {x, x, y};
    } else if (mode == 2) {
        int pairs = rnd.next(2, 8);
        for (int i = 0; i < pairs; ++i) {
            int x = randomValue(MIN_VALUE, 20000000);
            a.push_back(x);
            a.push_back(x);
        }
    } else if (mode == 3) {
        int n = rnd.next(5, 12);
        int base = rnd.next(MIN_VALUE, MAX_VALUE / n);
        for (int i = 0; i < n; ++i) {
            a.push_back(base * (i + 1));
        }
    } else if (mode == 4) {
        int n = rnd.next(6, 16);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) a.push_back(randomValue(MIN_VALUE, 3000000));
            if (bucket == 1) a.push_back(randomValue(3000000, 12000000));
            if (bucket == 2) a.push_back(randomValue(12000000, MAX_VALUE));
        }
    } else {
        int n = rnd.next(18, 24);
        for (int i = 0; i < n; ++i) {
            a.push_back(i % 2 == 0 ? randomValue(35000000, MAX_VALUE)
                                   : randomValue(MIN_VALUE, 5000000));
        }
    }

    shuffle(a.begin(), a.end());
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(4, 8);
    for (int tc = 0; tc < testCount; ++tc) {
        int mode = tc == 0 ? rnd.next(0, 2) : rnd.next(0, 5);
        vector<int> a = makeCase(mode);
        println((int)a.size());
        for (int value : a) {
            println(value);
        }
    }
    println(0);

    return 0;
}
