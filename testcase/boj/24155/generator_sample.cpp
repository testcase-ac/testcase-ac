#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 30);
    vector<int> scores;
    scores.reserve(n);

    if (mode == 0) {
        int score = rnd.next(0, 100);
        scores.assign(n, score);
    } else if (mode == 1) {
        int low = rnd.next(0, 25);
        int high = rnd.next(75, 100);
        for (int i = 0; i < n; ++i) {
            scores.push_back(rnd.next(0, 1) == 0 ? low : high);
        }
    } else if (mode == 2) {
        int lo = rnd.next(0, 95);
        int hi = rnd.next(lo, min(100, lo + rnd.next(0, 5)));
        for (int i = 0; i < n; ++i) {
            scores.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 3) {
        n = rnd.next(10, 30);
        for (int i = 0; i < n; ++i) {
            scores.push_back((i * rnd.next(3, 17) + rnd.next(0, 9)) % 101);
        }
        sort(scores.begin(), scores.end());
        if (rnd.next(0, 1) == 0) {
            reverse(scores.begin(), scores.end());
        }
    } else if (mode == 4) {
        n = rnd.next(1, 101);
        vector<int> pool;
        for (int s = 0; s <= 100; s += rnd.next(1, 10)) {
            pool.push_back(s);
        }
        for (int i = 0; i < n; ++i) {
            scores.push_back(rnd.any(pool));
        }
    } else if (mode == 5) {
        n = rnd.next(1, 30);
        int pivot = rnd.next(0, 100);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                scores.push_back(pivot);
            } else if (rnd.next(0, 1) == 0) {
                scores.push_back(rnd.next(0, pivot));
            } else {
                scores.push_back(rnd.next(pivot, 100));
            }
        }
        shuffle(scores.begin(), scores.end());
    } else {
        n = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            scores.push_back(rnd.next(0, 100));
        }
    }

    println(n);
    for (int score : scores) {
        println(score);
    }

    return 0;
}
