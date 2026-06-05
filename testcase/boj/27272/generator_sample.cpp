#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        int lo = rnd.next(1, 50);
        int hi = rnd.next(lo, 1000);
        for (int i = 0; i < 4; ++i) values.push_back(rnd.next(lo, hi));
    } else if (mode == 1) {
        int lo = rnd.next(-1000, -1);
        int hi = rnd.next(lo, -1);
        for (int i = 0; i < 4; ++i) values.push_back(rnd.next(lo, hi));
    } else if (mode == 2) {
        values = {
            -rnd.next(1, 1000),
            -rnd.next(1, 1000),
            rnd.next(1, 1000),
            rnd.next(1, 1000),
        };
    } else if (mode == 3) {
        int x = rnd.next(-1000, 1000);
        int y = rnd.next(-1000, 1000);
        values = {x, x, y, y};
    } else if (mode == 4) {
        int x = rnd.next(-1000, 1000);
        int y = rnd.next(-1000, 1000);
        values = {0, 0, x, y};
    } else if (mode == 5) {
        values = {-1000, 1000, rnd.next(-1000, 1000), rnd.next(-1000, 1000)};
    } else if (mode == 6) {
        for (int i = 0; i < 4; ++i) values.push_back(rnd.next(-20, 20));
    } else {
        for (int i = 0; i < 4; ++i) values.push_back(rnd.next(-1000, 1000));
    }

    shuffle(values.begin(), values.end());
    println(values);

    return 0;
}
