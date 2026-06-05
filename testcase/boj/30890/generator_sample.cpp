#include "testlib.h"

#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases = {
        {1, 1}, {1, 100}, {100, 1}, {100, 100},
        {2, 3}, {3, 2}, {4, 2}, {2, 4},
        {99, 100}, {100, 99}, {48, 96}, {96, 48},
    };

    int mode = rnd.next(0, 6);
    int x = 1;
    int y = 1;

    if (mode == 0) {
        tie(x, y) = rnd.any(cases);
    } else if (mode == 1) {
        x = rnd.next(1, 100);
        y = x;
    } else if (mode == 2) {
        x = rnd.next(1, 100);
        vector<int> multiples;
        for (int k = 1; x * k <= 100; ++k) {
            multiples.push_back(x * k);
        }
        y = rnd.any(multiples);
        if (rnd.next(0, 1)) {
            swap(x, y);
        }
    } else if (mode == 3) {
        do {
            x = rnd.next(1, 100);
            y = rnd.next(1, 100);
        } while (gcd(x, y) != 1);
    } else if (mode == 4) {
        int g = rnd.next(2, 20);
        int maxA = 100 / g;
        x = g * rnd.next(1, maxA);
        y = g * rnd.next(1, maxA);
    } else {
        x = rnd.next(1, 100);
        y = rnd.next(1, 100);
    }

    println(x, y);
    return 0;
}
