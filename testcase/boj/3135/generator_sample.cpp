#include "testlib.h"
#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;

int boundedFrequency(int x) {
    return min(999, max(1, x));
}

int differentFrequency(int x) {
    int y = rnd.next(1, 999);
    while (y == x) {
        y = rnd.next(1, 999);
    }
    return y;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = argc > 1 ? atoi(argv[1]) : rnd.next(0, 6);
    int n = rnd.next(1, 5);
    int a = rnd.next(1, 999);
    int b = differentFrequency(a);
    vector<int> presets;

    if (mode == 0) {
        int base = rnd.next(1, 999);
        int delta = rnd.any(vector<int>{-3, -2, -1, 1, 2, 3});
        a = base;
        b = boundedFrequency(base + delta);
        if (a == b) {
            b = differentFrequency(a);
        }
    } else if (mode == 1) {
        b = rnd.next(1, 999);
        a = differentFrequency(b);
        presets.push_back(b);
    } else if (mode == 2) {
        b = rnd.next(2, 998);
        a = differentFrequency(b);
        presets.push_back(b + rnd.any(vector<int>{-2, -1, 1, 2}));
    } else if (mode == 3) {
        a = rnd.any(vector<int>{1, 999});
        b = a == 1 ? 999 : 1;
        presets.push_back(rnd.any(vector<int>{1, 2, 998, 999}));
    } else if (mode == 4) {
        b = rnd.next(1, 999);
        a = differentFrequency(b);
        int repeated = rnd.next(1, 999);
        presets.assign(rnd.next(1, n), repeated);
    } else {
        a = rnd.next(1, 999);
        b = differentFrequency(a);
    }

    while ((int)presets.size() < n) {
        int choice = rnd.next(0, 4);
        if (choice == 0) {
            presets.push_back(b);
        } else if (choice == 1) {
            presets.push_back(boundedFrequency(b + rnd.next(-10, 10)));
        } else if (choice == 2) {
            presets.push_back(rnd.any(vector<int>{1, 999}));
        } else {
            presets.push_back(rnd.next(1, 999));
        }
    }

    shuffle(presets.begin(), presets.end());

    println(a, b);
    println(n);
    for (int i = 0; i < n; ++i) {
        println(presets[i]);
    }

    return 0;
}
