#include "testlib.h"

#include <array>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else {
        n = rnd.next(3, 18);
    }

    int k;
    if (mode == 0) {
        k = rnd.next(1, n);
    } else if (mode == 1) {
        k = 1;
    } else if (mode == 2) {
        k = n;
    } else {
        k = rnd.next(1, n);
    }

    vector<array<int, 3>> lectures;
    lectures.reserve(n);

    int favoredPair = rnd.next(0, 2);
    for (int i = 0; i < n; ++i) {
        array<int, 3> v{};

        if (mode == 0) {
            int x = rnd.next(0, 1) ? 10000 : 0;
            v = {x, x, x};
        } else if (mode == 1) {
            v = {rnd.next(0, 10000), rnd.next(0, 10000), rnd.next(0, 10000)};
        } else if (mode == 2) {
            int base = rnd.next(0, 100);
            v = {base, base, base};
            v[rnd.next(0, 2)] = rnd.next(0, 10000);
        } else if (mode == 3) {
            int high = rnd.next(7000, 10000);
            int low = rnd.next(0, 2000);
            v = {low, low, low};
            v[favoredPair] = high;
            v[(favoredPair + 1) % 3] = rnd.next(6000, 10000);
        } else if (mode == 4) {
            int pair = rnd.next(0, 2);
            int total = rnd.next(0, 10000);
            v[pair] = total;
            v[(pair + 1) % 3] = total;
            v[(pair + 2) % 3] = rnd.next(0, 10000);
        } else {
            int upper = rnd.next(0, 10000);
            v = {rnd.next(0, upper), rnd.next(0, upper), rnd.next(0, upper)};
        }

        lectures.push_back(v);
    }

    shuffle(lectures.begin(), lectures.end());

    println(n, k);
    for (const auto& v : lectures) {
        println(v[0], v[1], v[2]);
    }

    return 0;
}
