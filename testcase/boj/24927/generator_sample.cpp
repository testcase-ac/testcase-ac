#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int oddValue() {
    return rnd.next(0, 500000000) * 2 + 1;
}

int valueWithTwos(int twos) {
    int limit = 1000000000 >> twos;
    int odd = rnd.next(0, (limit - 1) / 2) * 2 + 1;
    return odd << twos;
}

void adjustTwos(vector<int>& twos, int target) {
    int current = 0;
    for (int value : twos) current += value;

    while (current < target) {
        int id = rnd.next((int)twos.size());
        int add = min(29 - twos[id], target - current);
        if (add == 0) continue;
        int delta = rnd.next(1, add);
        twos[id] += delta;
        current += delta;
    }

    while (current > target) {
        int id = rnd.next((int)twos.size());
        int remove = min(twos[id], current - target);
        if (remove == 0) continue;
        int delta = rnd.next(1, remove);
        twos[id] -= delta;
        current -= delta;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n = 1;
    int k = 0;
    vector<int> twos;

    if (mode == 0) {
        n = rnd.next(1, 20);
        k = 0;
        twos.assign(n, rnd.next(0, 29));
    } else if (mode == 1) {
        n = rnd.next(1, 25);
        k = rnd.next(1, 1000);
        twos.assign(n, 0);
    } else if (mode == 2) {
        n = rnd.next(1, 40);
        k = rnd.next(1, min(1000, 29 * n));
        twos.assign(n, 0);
        adjustTwos(twos, k);
    } else if (mode == 3) {
        n = rnd.next(2, 45);
        k = rnd.next(2, min(1000, 29 * n));
        twos.assign(n, 0);
        adjustTwos(twos, k - 1);
    } else if (mode == 4) {
        n = rnd.next(1, 35);
        k = rnd.next(1, 1000);
        twos.assign(n, 0);
        int id = rnd.next(n);
        twos[id] = rnd.next(20, 29);
        for (int i = 0; i < n; ++i) {
            if (i != id && rnd.next(4) == 0) twos[i] = rnd.next(1, 10);
        }
    } else if (mode == 5) {
        n = rnd.next(50, 220);
        k = rnd.next(1, 1000);
        twos.assign(n, 0);
        for (int i = 0; i < n; ++i) twos[i] = rnd.next(0, 6);
    } else {
        n = rnd.next(1, 30);
        k = rnd.next(1, 1000);
        twos.assign(n, 0);
        int target = rnd.next(0, min(1000, 29 * n));
        adjustTwos(twos, target);
    }

    vector<int> values;
    for (int twoCount : twos) {
        if (twoCount == 0) {
            values.push_back(oddValue());
        } else {
            values.push_back(valueWithTwos(twoCount));
        }
    }

    shuffle(values.begin(), values.end());

    println(n, k);
    for (int value : values) println(value);

    return 0;
}
