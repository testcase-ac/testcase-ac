#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static int randomK() {
    vector<int> edge = {1, 2, 9999, 10000};
    if (rnd.next(100) < 45) return rnd.any(edge);
    return rnd.next(1, 10000);
}

static vector<int> makeCounts(int size, int mode, int maxValue) {
    vector<int> values(size);
    for (int i = 0; i < size; ++i) {
        if (mode == 0) {
            values[i] = rnd.next(0, min(maxValue, 7));
        } else if (mode == 1) {
            values[i] = (rnd.next(100) < 65 ? 0 : rnd.next(1, min(maxValue, 25)));
        } else if (mode == 2) {
            int highStart = max(0, maxValue - min(maxValue, 50));
            values[i] = (i % 2 == 0 ? rnd.next(0, min(maxValue, 3)) : rnd.next(highStart, maxValue));
        } else if (mode == 3) {
            values[i] = rnd.next(max(0, maxValue - 200), maxValue);
        } else {
            values[i] = rnd.wnext(maxValue + 1, rnd.next(-3, 3));
        }
    }
    return values;
}

static void scaleDown(vector<int>& values, int targetSum) {
    int current = 0;
    for (int value : values) current += value;
    while (current > targetSum) {
        int idx = rnd.next((int)values.size());
        if (values[idx] == 0) continue;
        int take = rnd.next(1, min(values[idx], current - targetSum));
        values[idx] -= take;
        current -= take;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 60 : 14);
    int m = rnd.next(1, mode == 5 ? 60 : 14);
    int maxValue = (mode >= 3 ? 10000 : rnd.next(5, 200));

    vector<int> oldFloors = makeCounts(n, mode % 5, maxValue);
    vector<int> newFloors = makeCounts(m, (mode + rnd.next(1, 4)) % 5, maxValue);

    if (mode == 0) {
        oldFloors[rnd.next(n)] = rnd.next(1, min(maxValue, 20));
        newFloors[rnd.next(m)] = rnd.next(1, min(maxValue, 20));
    } else if (mode == 1) {
        scaleDown(newFloors, max(0, rnd.next(0, 40)));
    } else if (mode == 2) {
        scaleDown(oldFloors, max(0, rnd.next(0, 40)));
    } else if (mode == 4) {
        oldFloors.front() = 10000;
        newFloors.back() = 10000;
    }

    println(n, m, randomK());
    for (int value : oldFloors) println(value);
    for (int value : newFloors) println(value);

    return 0;
}
