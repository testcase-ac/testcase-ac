#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxA = (1 << 25) - 1;
    int n = rnd.next(8, 40);
    vector<int> values;

    values.push_back(2);
    values.push_back(3);
    values.push_back(maxA);

    while ((int)values.size() < n) {
        int mode = rnd.next(6);
        int x;

        if (mode == 0) {
            x = 1 << rnd.next(1, 24);
        } else if (mode == 1) {
            x = (1 << rnd.next(2, 25)) - 1;
        } else if (mode == 2) {
            int bit = rnd.next(2, 24);
            int delta = rnd.next(-2, 2);
            x = (1 << bit) + delta;
        } else if (mode == 3) {
            int bit = rnd.next(2, 25);
            int delta = rnd.next(-2, 2);
            x = ((1 << bit) - 1) + delta;
        } else if (mode == 4) {
            int bit = rnd.next(1, 24);
            x = (1 << bit) | rnd.next(0, (1 << bit) - 1);
        } else {
            x = rnd.next(2, maxA);
        }

        x = max(2, min(maxA, x));
        values.push_back(x);
    }

    shuffle(values.begin(), values.end());

    println((int)values.size());
    for (int x : values) {
        println(x);
    }

    return 0;
}
