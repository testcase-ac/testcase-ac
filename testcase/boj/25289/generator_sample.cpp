#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampValue(int x) {
    return max(1, min(100, x));
}

vector<int> makeArithmeticRun(int start, int diff, int len) {
    vector<int> values;
    values.reserve(len);
    for (int i = 0; i < len; ++i) values.push_back(start + diff * i);
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    vector<int> a;

    if (mode == 0) {
        int n = rnd.next(1, 4);
        a.assign(n, rnd.next(1, 100));
    } else if (mode == 1) {
        int n = rnd.next(8, 45);
        int low = rnd.next(1, 90);
        int high = rnd.next(low, min(100, low + rnd.next(0, 15)));
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(low, high));
    } else if (mode == 2) {
        int diff = rnd.next(1, 12);
        int len = rnd.next(3, max(3, min(20, 100 / diff)));
        int start = rnd.next(1, 100 - diff * (len - 1));
        a = makeArithmeticRun(start, diff, len);
    } else if (mode == 3) {
        int diff = rnd.next(1, 12);
        int len = rnd.next(3, max(3, min(20, 100 / diff)));
        int start = rnd.next(1 + diff * (len - 1), 100);
        a = makeArithmeticRun(start, -diff, len);
    } else if (mode == 4) {
        int diff = rnd.next(1, 10);
        int len = rnd.next(4, max(4, min(18, 100 / diff)));
        int start = rnd.next(1, 100 - diff * (len - 1));
        vector<int> run = makeArithmeticRun(start, diff, len);
        for (int x : run) {
            if (rnd.next(0, 2) == 0) a.push_back(rnd.next(1, 100));
            a.push_back(x);
            if (rnd.next(0, 2) == 0) a.push_back(rnd.next(1, 100));
        }
    } else if (mode == 5) {
        int n = rnd.next(10, 50);
        for (int i = 0; i < n; ++i) a.push_back(i % 2 == 0 ? rnd.next(1, 8) : rnd.next(93, 100));
    } else {
        int n = rnd.next(20, 70);
        vector<int> pool;
        int poolSize = rnd.next(2, 8);
        for (int i = 0; i < poolSize; ++i) pool.push_back(rnd.next(1, 100));
        sort(pool.begin(), pool.end());
        pool.erase(unique(pool.begin(), pool.end()), pool.end());
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    }

    println((int)a.size());
    println(a);
    return 0;
}
