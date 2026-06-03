#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int sizeMode = rnd.next(0, 9);
    if (sizeMode < 6) {
        n = rnd.next(1, 3) * 10;
    } else if (sizeMode < 9) {
        n = rnd.next(4, 7) * 10;
    } else {
        n = rnd.next(8, 10) * 10;
    }

    vector<int> pool;
    int scoreMode = rnd.next(0, 5);
    if (scoreMode == 0) {
        for (int i = 1; i <= 100; ++i) pool.push_back(i);
    } else if (scoreMode == 1) {
        for (int i = 100; i >= 1; --i) pool.push_back(i);
    } else if (scoreMode == 2) {
        for (int i = 1; i <= 100; i += 2) pool.push_back(i);
        for (int i = 2; i <= 100; i += 2) pool.push_back(i);
    } else {
        for (int i = 1; i <= 100; ++i) pool.push_back(i);
        shuffle(pool.begin(), pool.end());
    }

    vector<int> scores(pool.begin(), pool.begin() + n);
    if (scoreMode == 4) {
        sort(scores.begin(), scores.end());
    } else if (scoreMode == 5) {
        sort(scores.rbegin(), scores.rend());
    } else if (rnd.next(0, 1)) {
        shuffle(scores.begin(), scores.end());
    }

    int x = rnd.next(1, 10) * 10;

    int y;
    int thresholdMode = rnd.next(0, 5);
    if (thresholdMode == 0) {
        y = 1;
    } else if (thresholdMode == 1) {
        y = 100;
    } else if (thresholdMode == 2) {
        y = rnd.any(scores);
    } else if (thresholdMode == 3) {
        y = max(1, rnd.any(scores) - 1);
    } else if (thresholdMode == 4) {
        y = min(100, rnd.any(scores) + 1);
    } else {
        y = rnd.next(1, 100);
    }

    println(n);
    println(scores);
    println(x, y);

    return 0;
}
