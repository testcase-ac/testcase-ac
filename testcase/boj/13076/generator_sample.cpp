#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> pool = {
        2, 3, 4, 5, 6, 7, 8, 9, 10,
        12, 16, 25, 27, 32, 49, 64, 81,
        97, 101, 127, 210, 256, 512, 997,
        999, 1000, 1024, 4096, 9999, 10000
    };

    int mode = rnd.next(0, 4);
    int t = rnd.next(1, 24);

    if (mode == 0) {
        int start = rnd.next(2, 80);
        int len = rnd.next(1, min(24, 10001 - start));
        pool.clear();
        for (int i = 0; i < len; ++i) {
            pool.push_back(start + i);
        }
    } else if (mode == 1) {
        pool.clear();
        t = rnd.next(8, 24);
        for (int i = 0; i < t; ++i) {
            pool.push_back(rnd.next(2, 150));
        }
    } else if (mode == 2) {
        pool.clear();
        t = rnd.next(8, 24);
        for (int i = 0; i < t; ++i) {
            int a = rnd.next(2, 100);
            int b = rnd.next(2, 100);
            pool.push_back(min(10000, a * b));
        }
    } else if (mode == 3) {
        t = rnd.next(10, 30);
        for (int i = 0; i < t; ++i) {
            pool.push_back(rnd.next(9000, 10000));
        }
    } else {
        t = rnd.next(1, 40);
        for (int i = 0; i < t; ++i) {
            pool.push_back(rnd.next(2, 10000));
        }
    }

    shuffle(pool.begin(), pool.end());
    t = min(t, int(pool.size()));
    pool.resize(t);

    println(t);
    for (int n : pool) {
        println(n);
    }

    return 0;
}
