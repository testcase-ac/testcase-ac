#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else if (mode == 2) {
        n = rnd.next(20, 80);
    } else {
        n = rnd.next(5, 30);
    }

    vector<array<int, 3>> rows(n);

    if (mode == 0) {
        rows[0] = {rnd.next(0, 9), rnd.next(0, 9), rnd.next(0, 9)};
    } else if (mode == 1) {
        int lo = rnd.next(0, 5);
        int hi = rnd.next(lo, 9);
        for (auto& row : rows) {
            row = {rnd.next(lo, hi), rnd.next(lo, hi), rnd.next(lo, hi)};
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int hot = rnd.next(0, 2);
            rows[i] = {rnd.next(0, 2), rnd.next(0, 2), rnd.next(0, 2)};
            rows[i][hot] = rnd.next(7, 9);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int edge = (i + rnd.next(0, 1)) % 2 == 0 ? 0 : 2;
            rows[i] = {rnd.next(0, 3), rnd.next(4, 6), rnd.next(0, 3)};
            rows[i][edge] = rnd.next(7, 9);
        }
    } else if (mode == 4) {
        int first = rnd.next(0, 9);
        int second = rnd.next(0, 9);
        for (int i = 0; i < n; ++i) {
            int a = (i % 2 == 0) ? first : second;
            int b = 9 - a;
            rows[i] = {a, rnd.next(0, 9), b};
            if (rnd.next(0, 3) == 0) {
                swap(rows[i][0], rows[i][2]);
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            int value = (i % 3 == 0) ? 0 : 9;
            rows[i] = {value, value, value};
            rows[i][rnd.next(0, 2)] = rnd.next(0, 9);
        }
    } else {
        array<int, 3> base = {0, 4, 9};
        for (int i = 0; i < n; ++i) {
            shuffle(base.begin(), base.end());
            rows[i] = base;
            if (rnd.next(0, 2) == 0) {
                rows[i][rnd.next(0, 2)] = rnd.next(0, 9);
            }
        }
    }

    println(n);
    for (const auto& row : rows) {
        println(row[0], row[1], row[2]);
    }

    return 0;
}
