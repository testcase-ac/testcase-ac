#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedScore(int lo, int hi) {
    return rnd.next(max(0, lo), min(100, hi));
}

vector<int> makeTricks(int mode, int base) {
    vector<int> tricks(5);
    if (mode == 0) {
        fill(tricks.begin(), tricks.end(), base);
    } else if (mode == 1) {
        tricks = {0, 100, boundedScore(base - 5, base + 5), 100, 0};
    } else if (mode == 2) {
        for (int& trick : tricks) trick = boundedScore(base - 20, base + 20);
    } else {
        for (int i = 0; i < 5; ++i) tricks[i] = boundedScore(i * 18, i * 18 + 25);
        shuffle(tricks.begin(), tricks.end());
    }
    return tricks;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 12);
    } else {
        n = rnd.next(8, 25);
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        int base;
        if (mode == 0) {
            base = rnd.any(vector<int>{0, 1, 50, 99, 100});
        } else if (mode == 1) {
            base = (i % 2 == 0) ? rnd.next(80, 100) : rnd.next(0, 20);
        } else {
            base = rnd.next(0, 100);
        }

        int run1 = boundedScore(base - rnd.next(0, 30), base + rnd.next(0, 30));
        int run2 = boundedScore(base - rnd.next(0, 30), base + rnd.next(0, 30));
        if (mode == 1 && i % 3 == 0) {
            run1 = rnd.any(vector<int>{0, 100});
            run2 = 100 - run1;
        }

        vector<int> tricks = makeTricks((mode + i + rnd.next(4)) % 4, base);
        println(run1, run2, tricks[0], tricks[1], tricks[2], tricks[3], tricks[4]);
    }

    return 0;
}
