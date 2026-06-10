#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 6);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int m = rnd.next(1, 10);
        vector<int> values;

        if (mode == 0) {
            int base = rnd.next(1, 8);
            for (int i = 0; i < m; ++i) values.push_back(base);
        } else if (mode == 1) {
            int start = rnd.next(1, 8);
            for (int i = 0; i < m; ++i) values.push_back(start + i);
        } else if (mode == 2) {
            for (int i = 0; i < m; ++i) values.push_back(rnd.next(1, 10));
            sort(values.begin(), values.end());
            if (rnd.next(0, 1)) reverse(values.begin(), values.end());
        } else if (mode == 3) {
            vector<int> pool = {1, 2, 3, 5, 7, 11, 13, 17, 19};
            for (int i = 0; i < m; ++i) values.push_back(rnd.any(pool));
        } else if (mode == 4) {
            int lo = rnd.next(1, 12);
            int hi = rnd.next(lo, 20);
            for (int i = 0; i < m; ++i) values.push_back(rnd.next(lo, hi));
        } else {
            for (int i = 0; i < m; ++i) {
                values.push_back(i % 2 == 0 ? rnd.next(1, 5) : rnd.next(12, 20));
            }
            shuffle(values.begin(), values.end());
        }

        println(m);
        println(values);
    }

    return 0;
}
