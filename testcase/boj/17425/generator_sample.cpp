#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t = rnd.next(1, 30);
    vector<int> values;
    values.reserve(t);

    auto add = [&](int value) {
        values.push_back(max(1, min(1000000, value)));
    };

    if (mode == 0) {
        t = rnd.next(1, 12);
        for (int i = 0; i < t; ++i) add(rnd.next(1, 25));
    } else if (mode == 1) {
        t = rnd.next(8, 24);
        vector<int> landmarks = {1, 2, 3, 4, 6, 10, 12, 24, 36, 60, 72, 120, 180, 240, 360, 720};
        for (int i = 0; i < t; ++i) add(rnd.any(landmarks) + rnd.next(-2, 2));
    } else if (mode == 2) {
        t = rnd.next(6, 20);
        for (int i = 0; i < t; ++i) {
            int base = rnd.next(1, 1000);
            add(base * base + rnd.next(-base, base));
        }
    } else if (mode == 3) {
        t = rnd.next(4, 18);
        for (int i = 0; i < t; ++i) add(1000000 - rnd.next(0, 5000));
    } else if (mode == 4) {
        t = rnd.next(10, 30);
        int repeated = rnd.next(1, 1000000);
        for (int i = 0; i < t; ++i) {
            if (rnd.next(0, 99) < 35) add(repeated);
            else add(rnd.next(1, 1000000));
        }
    } else {
        t = rnd.next(12, 30);
        for (int i = 0; i < t; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) add(rnd.next(1, 100));
            else if (bucket == 1) add(rnd.next(1000, 10000));
            else if (bucket == 2) add(rnd.next(100000, 200000));
            else add(rnd.next(900000, 1000000));
        }
    }

    if (rnd.next(0, 99) < 40) sort(values.begin(), values.end());
    else shuffle(values.begin(), values.end());

    println((int)values.size());
    for (int value : values) println(value);

    return 0;
}
