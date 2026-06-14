#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int chooseK(int minA) {
    int mode = rnd.next(0, 3);
    if (mode == 0) return 1;
    if (mode == 1) return minA - 1;
    return rnd.next(1, minA - 1);
}

vector<int> takeDistinct(vector<int> pool, int n) {
    shuffle(pool.begin(), pool.end());
    pool.resize(n);
    return pool;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<int> a;

    if (mode == 0) {
        int n = rnd.next(2, 4);
        vector<int> pool;
        for (int x = 3; x <= 12; ++x) pool.push_back(x);
        a = takeDistinct(pool, n);
    } else if (mode == 1) {
        int n = rnd.next(6, 8);
        vector<int> pool;
        for (int x = 24; x <= 40; ++x) pool.push_back(x);
        a = takeDistinct(pool, n);
    } else if (mode == 2) {
        int n = rnd.next(2, 8);
        vector<int> pool = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
        a = takeDistinct(pool, n);
    } else if (mode == 3) {
        int n = rnd.next(3, 8);
        vector<int> pool = {4, 6, 8, 9, 10, 12, 14, 15, 16, 18,
                            20, 21, 24, 27, 28, 30, 32, 36, 40};
        a = takeDistinct(pool, n);
    } else {
        int n = rnd.next(2, 8);
        vector<int> pool;
        for (int x = 3; x <= 40; ++x) pool.push_back(x);
        a = takeDistinct(pool, n);
    }

    int minA = *min_element(a.begin(), a.end());
    int k = chooseK(minA);

    println(k, static_cast<int>(a.size()));
    println(a);

    return 0;
}
