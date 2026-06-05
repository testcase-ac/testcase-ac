#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string formatProbability(int hundredths, int style) {
    if (hundredths == 100) {
        if (style == 0) return "1";
        if (style == 1) return "1.0";
        return "1.00";
    }

    int wholeTenths = hundredths / 10;
    if (hundredths % 10 == 0 && style == 0) {
        return "0." + to_string(wholeTenths);
    }

    if (hundredths < 10) {
        return "0.0" + to_string(hundredths);
    }
    return "0." + to_string(hundredths);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> p;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        for (int i = 0; i < 10; ++i) p.push_back(rnd.next(1, 100));
    } else if (mode == 1) {
        int start = rnd.next(1, 10);
        for (int i = 0; i < 10; ++i) p.push_back(min(100, start + i * rnd.next(1, 4)));
    } else if (mode == 2) {
        for (int i = 0; i < 10; ++i) p.push_back(rnd.next(1, 12));
    } else if (mode == 3) {
        for (int i = 0; i < 10; ++i) p.push_back(rnd.next(85, 100));
    } else if (mode == 4) {
        int center = rnd.next(20, 90);
        for (int i = 0; i < 10; ++i) p.push_back(max(1, min(100, center + rnd.next(-8, 8))));
    } else {
        vector<int> pool = {1, 2, 9, 10, 11, 50, 75, 90, 99, 100};
        shuffle(pool.begin(), pool.end());
        p = pool;
    }

    shuffle(p.begin(), p.end());
    for (int value : p) {
        println(formatProbability(value, rnd.next(0, 2)));
    }

    return 0;
}
