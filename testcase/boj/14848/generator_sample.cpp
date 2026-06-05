#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    long long n;
    int k;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1LL, 30LL);
        k = rnd.next(1, 8);
        for (int i = 0; i < k; ++i) a.push_back(rnd.next(1, 12));
    } else if (mode == 1) {
        n = rnd.next(900000000LL, 1000000000LL);
        k = 15;
        for (int i = 0; i < k; ++i) a.push_back(rnd.next(1, 100));
    } else if (mode == 2) {
        n = rnd.next(1000LL, 1000000LL);
        k = rnd.next(8, 15);
        int base = rnd.next(1, 10);
        for (int i = 0; i < k; ++i) a.push_back(min(100, base * rnd.next(1, 10)));
    } else if (mode == 3) {
        n = rnd.next(100000LL, 1000000000LL);
        vector<int> pool = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
        shuffle(pool.begin(), pool.end());
        k = rnd.next(5, 15);
        a.assign(pool.begin(), pool.begin() + k);
    } else if (mode == 4) {
        n = rnd.next(1LL, 1000000000LL);
        k = rnd.next(10, 15);
        for (int i = 0; i < k; ++i) a.push_back(rnd.any(vector<int>{1, 2, 4, 5, 10, 20, 25, 50, 100}));
    } else {
        n = rnd.next(31LL, 1000000000LL);
        k = rnd.next(1, 15);
        for (int i = 0; i < k; ++i) a.push_back(rnd.next(1, 100));
    }

    shuffle(a.begin(), a.end());
    println(n, k);
    println(a);

    return 0;
}
