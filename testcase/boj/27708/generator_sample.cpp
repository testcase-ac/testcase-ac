#include "testlib.h"

#include <algorithm>
#include <climits>
#include <set>
#include <vector>

using namespace std;

vector<int> compactValues(int n) {
    int base = rnd.next(-20, 20);
    int step = rnd.next(1, 5);
    vector<int> values;
    values.reserve(n);
    for (int i = 0; i < n; ++i) {
        values.push_back(base + i * step);
    }
    return values;
}

vector<int> wideValues(int n) {
    set<int> used;
    used.insert(INT_MIN);
    used.insert(INT_MAX);
    used.insert(0);
    while (static_cast<int>(used.size()) < n) {
        used.insert(rnd.next(INT_MIN, INT_MAX));
    }
    vector<int> values(used.begin(), used.end());
    shuffle(values.begin(), values.end());
    values.resize(n);
    return values;
}

void arrangeValues(vector<int>& values, int mode) {
    sort(values.begin(), values.end());

    if (mode == 0) {
        return;
    }
    if (mode == 1) {
        reverse(values.begin(), values.end());
        return;
    }
    if (mode == 2) {
        if (values.size() >= 4) {
            swap(values[1], values[2]);
        }
        return;
    }
    if (mode == 3) {
        if (values.size() >= 4) {
            reverse(values.begin() + 1, values.end() - 1);
        }
        return;
    }

    shuffle(values.begin(), values.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        printf("\n");

        int sizeMode = rnd.next(0, 5);
        int n;
        if (sizeMode == 0) {
            n = 3;
        } else if (sizeMode == 1) {
            n = rnd.next(4, 8);
        } else if (sizeMode == 2) {
            n = rnd.next(9, 20);
        } else if (sizeMode == 3) {
            n = rnd.next(21, 40);
        } else {
            n = rnd.next(80, 140);
        }

        vector<int> values = rnd.next(0, 3) == 0 ? wideValues(n) : compactValues(n);
        arrangeValues(values, rnd.next(0, 4));

        println(n);
        println(values);
    }

    return 0;
}
