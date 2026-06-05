#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampScore(int x) {
    return max(0, min(10000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 24);
    vector<int> scores(n);

    if (mode == 0) {
        int value = rnd.next(0, 10000);
        fill(scores.begin(), scores.end(), value);
    } else if (mode == 1) {
        int start = rnd.next(0, 4000);
        int step = rnd.next(0, 800);
        for (int i = 0; i < n; ++i) scores[i] = clampScore(start + i * step);
    } else if (mode == 2) {
        int start = rnd.next(6000, 10000);
        int step = rnd.next(0, 800);
        for (int i = 0; i < n; ++i) scores[i] = clampScore(start - i * step);
    } else if (mode == 3) {
        int low = rnd.next(0, 2000);
        int high = rnd.next(8000, 10000);
        for (int i = 0; i < n; ++i) {
            scores[i] = rnd.next() < 0.35 ? low : high;
        }
    } else if (mode == 4) {
        int base = rnd.next(0, 10000);
        for (int i = 0; i < n; ++i) scores[i] = clampScore(base + rnd.next(-1200, 1200));
    } else {
        int low = rnd.next(0, 5000);
        int high = rnd.next(low, 10000);
        for (int i = 0; i < n; ++i) scores[i] = rnd.next(low, high);
        scores[rnd.next(n)] = 0;
        scores[rnd.next(n)] = 10000;
    }

    println(n);
    println(scores);

    return 0;
}
