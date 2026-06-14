#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampScore(int x) {
    return max(0, min(100, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int n = 100;
    const vector<int> cuts = {4, 11, 23, 40, 60, 77, 89, 96, 100};
    vector<int> a;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int score = rnd.next(0, 100);
        a.assign(n, score);
    } else if (mode == 1) {
        int lo = rnd.next(0, 100);
        int hi = rnd.next(lo, 100);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 2) {
        int start = rnd.next(0, 100);
        int step = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) {
            a.push_back(clampScore(start + i * step));
        }
    } else if (mode == 3) {
        int highCount = rnd.any(cuts);
        highCount = clampScore(highCount + rnd.next(-3, 3));
        int high = rnd.next(60, 100);
        int low = rnd.next(0, high);
        for (int i = 0; i < highCount; ++i) {
            a.push_back(high);
        }
        while ((int)a.size() < n) {
            a.push_back(rnd.next(0, low));
        }
    } else if (mode == 4) {
        int score = rnd.next(10, 95);
        int tieCount = rnd.next(1, 35);
        for (int i = 0; i < tieCount; ++i) {
            a.push_back(score);
        }
        while ((int)a.size() < n) {
            if (rnd.next(0, 1) == 0) {
                a.push_back(rnd.next(0, score));
            } else {
                a.push_back(rnd.next(score, 100));
            }
        }
    } else {
        int cur = rnd.next(90, 100);
        int prev = 0;
        for (int cut : cuts) {
            int count = cut - prev;
            int bucketScore = clampScore(cur + rnd.next(-1, 1));
            for (int i = 0; i < count; ++i) {
                a.push_back(bucketScore);
            }
            cur -= rnd.next(0, 8);
            prev = cut;
        }
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);
    return 0;
}
