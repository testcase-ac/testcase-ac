#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxX = 2000000000;
    int mode = rnd.next(0, 5);
    int t;
    vector<int> xs;

    if (mode == 0) {
        t = rnd.next(1, 12);
        for (int i = 0; i < t; ++i) xs.push_back(rnd.next(1, 12));
    } else if (mode == 1) {
        vector<int> pool = {1, 2, 3, 4, 5, 10, 99, 100, maxX - 1, maxX};
        shuffle(pool.begin(), pool.end());
        t = rnd.next(1, (int)pool.size());
        xs.assign(pool.begin(), pool.begin() + t);
    } else if (mode == 2) {
        t = rnd.next(5, 30);
        int base = rnd.next(1, 1000);
        int step = rnd.next(1, 1000000);
        for (int i = 0; i < t; ++i) {
            long long value = (long long)base + (long long)i * step;
            xs.push_back((int)min<long long>(value, maxX));
        }
    } else if (mode == 3) {
        t = rnd.next(10, 80);
        int upper = rnd.next(1, 100000);
        for (int i = 0; i < t; ++i) xs.push_back(rnd.next(1, upper));
    } else if (mode == 4) {
        t = rnd.next(20, 150);
        for (int i = 0; i < t; ++i) {
            if (rnd.next(0, 3) == 0) {
                xs.push_back(rnd.next(maxX - 1000, maxX));
            } else {
                xs.push_back(rnd.next(1, 1000));
            }
        }
    } else {
        t = rnd.next(1000, 5000);
        for (int i = 0; i < t; ++i) xs.push_back(rnd.next(1, maxX));
    }

    shuffle(xs.begin(), xs.end());
    println((int)xs.size());
    for (int x : xs) println(x);

    return 0;
}
