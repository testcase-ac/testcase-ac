#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(3, 16);
    vector<int> values;
    values.reserve(caseCount);

    int mode = rnd.next(0, 5);
    for (int i = 0; i < caseCount; ++i) {
        int n;
        if (mode == 0) {
            n = rnd.next(1, 30);
        } else if (mode == 1) {
            int base = rnd.next(1, 3200);
            int delta = rnd.next(-3, 3);
            n = base * base + delta;
            n = max(1, min(n, 10000000));
        } else if (mode == 2) {
            n = rnd.next(1, 1000);
        } else if (mode == 3) {
            n = rnd.next(100000, 10000000);
        } else if (mode == 4) {
            int step = rnd.next(0, 200000);
            n = 10000000 - step;
        } else {
            n = rnd.next(1, 10000000);
        }
        values.push_back(n);
    }

    values.push_back(1);
    values.push_back(2);
    values.push_back(10000000);
    shuffle(values.begin(), values.end());

    for (int n : values) {
        println(n);
    }
    println(0);

    return 0;
}
