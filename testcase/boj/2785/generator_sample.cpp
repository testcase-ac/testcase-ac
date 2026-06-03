#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 2;
    vector<int> lengths;

    if (mode == 0) {
        n = rnd.next(2, 4);
        lengths.assign(n, 1);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        lengths.assign(n, 1);
        lengths[rnd.next(n)] = rnd.next(2, 1000000);
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        int small = rnd.next(1, 3);
        int large = rnd.next(4, 30);
        for (int i = 0; i < n; ++i) {
            lengths.push_back(rnd.next() < 0.7 ? rnd.next(1, small) : rnd.next(small + 1, large));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 25);
        int base = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            lengths.push_back(max(1, base + rnd.next(-2, 2)));
        }
    } else if (mode == 4) {
        n = rnd.next(10, 40);
        for (int i = 0; i < n; ++i) {
            lengths.push_back(i % 2 == 0 ? 1 : rnd.next(2, 100));
        }
    } else if (mode == 5) {
        n = rnd.next(2, 30);
        for (int i = 0; i < n; ++i) {
            lengths.push_back(rnd.next(1, 1000000));
        }
    } else {
        n = rnd.next(2, 60);
        int pivot = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            lengths.push_back(i < pivot ? rnd.next(1, 2) : rnd.next(3, 12));
        }
    }

    shuffle(lengths.begin(), lengths.end());

    println(n);
    println(lengths);

    return 0;
}
