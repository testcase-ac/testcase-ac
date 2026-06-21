#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);

    vector<long long> pool;
    if (mode == 4) {
        n = 1;
        m = 1;
    }

    if (mode == 0) {
        pool = {0};
    } else if (mode == 1) {
        int top = rnd.next(1, 8);
        pool = {0, top};
    } else if (mode == 2) {
        int top = rnd.next(2, 15);
        pool = {0, 1, top / 2, top};
    } else if (mode == 3) {
        int top = rnd.next(1, 30);
        for (int x = 0; x <= top; x += max(1, top / rnd.next(2, 5))) {
            pool.push_back(x);
        }
        pool.push_back(top);
    } else if (mode == 4) {
        long long top = rnd.next(1000000000LL, 2147483647LL);
        pool = {0, top};
    } else {
        int top = rnd.next(1, 50);
        pool = {0, rnd.next(0, top), rnd.next(0, top), top};
    }

    sort(pool.begin(), pool.end());
    pool.erase(unique(pool.begin(), pool.end()), pool.end());

    vector<long long> front(n), side(m);
    for (long long& height : front) {
        height = rnd.any(pool);
    }
    for (long long& height : side) {
        height = rnd.any(pool);
    }

    long long shared_top = pool.back();
    front[rnd.next(n)] = shared_top;
    side[rnd.next(m)] = shared_top;

    if (mode == 5 && shared_top < 2147483647LL) {
        if (rnd.next(0, 1) == 0) {
            front[rnd.next(n)] = shared_top + 1;
        } else {
            side[rnd.next(m)] = shared_top + 1;
        }
    }

    int ordering = rnd.next(0, 3);
    if (ordering == 1) {
        sort(front.begin(), front.end());
        sort(side.begin(), side.end());
    } else if (ordering == 2) {
        sort(front.rbegin(), front.rend());
        sort(side.rbegin(), side.rend());
    } else if (ordering == 3) {
        shuffle(front.begin(), front.end());
        shuffle(side.begin(), side.end());
    }

    println(n, m);
    for (long long height : front) {
        println(height);
    }
    for (long long height : side) {
        println(height);
    }

    return 0;
}
