#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values;
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        int hi = rnd.next(5, 18);
        set<int> picked;
        picked.insert(1);
        while ((int)picked.size() < 5) {
            picked.insert(rnd.next(2, hi));
        }
        values.assign(picked.begin(), picked.end());
    } else if (mode == 1) {
        set<int> picked;
        while ((int)picked.size() < 5) {
            picked.insert(rnd.next(80, 100));
        }
        values.assign(picked.begin(), picked.end());
    } else if (mode == 2) {
        int base = rnd.any(vector<int>{2, 3, 4, 5, 6, 7, 10, 12});
        set<int> picked;
        for (int mul = 1; mul * base <= 100 && (int)picked.size() < 5; ++mul) {
            if (rnd.next(0, 2) != 0) {
                picked.insert(mul * base);
            }
        }
        while ((int)picked.size() < 5) {
            picked.insert(base * rnd.next(1, 100 / base));
        }
        values.assign(picked.begin(), picked.end());
    } else if (mode == 3) {
        vector<int> pool = {6, 10, 14, 15, 21, 22, 26, 33, 34, 35, 38, 39,
                            46, 55, 57, 58, 62, 65, 69, 74, 77, 82, 85, 86,
                            87, 91, 93, 94, 95};
        shuffle(pool.begin(), pool.end());
        values.assign(pool.begin(), pool.begin() + 5);
    } else {
        set<int> picked;
        int lo = rnd.next(1, 50);
        int hi = rnd.next(max(lo + 4, 55), 100);
        while ((int)picked.size() < 5) {
            picked.insert(rnd.next(lo, hi));
        }
        values.assign(picked.begin(), picked.end());
    }

    shuffle(values.begin(), values.end());
    println(values);

    return 0;
}
