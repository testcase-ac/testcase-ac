#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 2;
    vector<int> lengths;

    if (mode == 0) {
        n = rnd.next(2, 12);
        int hi = rnd.next(3, 80);
        for (int i = 0; i < n; ++i) {
            lengths.push_back(rnd.next(1, hi));
        }
    } else if (mode == 1) {
        n = rnd.next(2, 25);
        int value = rnd.next(1, 200);
        lengths.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(3, 30);
        int small_hi = rnd.next(1, 9);
        for (int i = 0; i + 1 < n; ++i) {
            lengths.push_back(rnd.next(1, small_hi));
        }
        lengths.push_back(rnd.next(1000, 50000));
    } else if (mode == 3) {
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            lengths.push_back(rnd.next(45000, 50000));
        }
    } else if (mode == 4) {
        n = rnd.next(6, 60);
        int base = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            lengths.push_back(min(50000, base * rnd.next(1, 20)));
        }
    } else {
        n = rnd.next(4, 30);
        int current = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            current = min(50000, current + rnd.next(0, current + 3));
            lengths.push_back(current);
        }
    }

    int order = rnd.next(0, 2);
    if (order == 0) {
        shuffle(lengths.begin(), lengths.end());
    } else if (order == 1) {
        sort(lengths.begin(), lengths.end());
    } else {
        sort(lengths.rbegin(), lengths.rend());
    }

    println(n);
    for (int length : lengths) {
        println(length);
    }

    return 0;
}
