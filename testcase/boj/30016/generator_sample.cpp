#include "testlib.h"

#include <vector>

using namespace std;

vector<int> makeNondecreasingRow(int t, int mode) {
    vector<int> row(t + 1);
    int value = 0;

    if (mode == 0) {
        value = rnd.next(0, 20);
        for (int j = 0; j <= t; ++j) {
            row[j] = value;
        }
        return row;
    }

    if (mode == 1) {
        int jumpAt = rnd.next(0, t);
        int low = rnd.next(0, 30);
        int high = rnd.next(low, 10000);
        for (int j = 0; j <= t; ++j) {
            row[j] = (j < jumpAt ? low : high);
        }
        return row;
    }

    int maxStep = (mode == 2 ? rnd.next(0, 5) : rnd.next(100, 2500));
    value = rnd.next(0, 25);
    row[0] = value;
    for (int j = 1; j <= t; ++j) {
        if (mode == 3 && rnd.next(0, 4) == 0) {
            value = rnd.next(value, 10000);
        } else {
            value += rnd.next(0, maxStep);
        }
        if (value > 10000) {
            value = 10000;
        }
        row[j] = value;
    }

    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n = (sizeMode == 0 ? 1 : rnd.next(2, 10));
    int t = (sizeMode == 1 ? 1 : rnd.next(2, 15));
    if (sizeMode == 3) {
        n = rnd.next(8, 14);
        t = rnd.next(8, 18);
    }

    println(n, t);

    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(0, 3);
        vector<int> scores = makeNondecreasingRow(t, mode);
        if (rnd.next(0, 9) == 0) {
            scores[t] = 10000;
        }
        println(scores);
    }

    int fatigueMode = rnd.next(0, 3);
    vector<int> fatigue = makeNondecreasingRow(t, fatigueMode);
    if (rnd.next(0, 2) == 0) {
        fatigue[0] = 0;
    }
    println(fatigue);

    return 0;
}
