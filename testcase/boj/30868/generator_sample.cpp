#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> candidates;
    for (int x : {1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 19, 20, 21, 24, 25,
                  26, 49, 50, 51, 95, 96, 99, 100}) {
        candidates.push_back(x);
    }

    int extraCount = rnd.next(5, 25);
    for (int i = 0; i < extraCount; ++i) {
        int mode = rnd.next(0, 3);
        int value;
        if (mode == 0) {
            value = rnd.next(1, 100);
        } else if (mode == 1) {
            int base = rnd.next(1, 20) * 5;
            value = base + rnd.next(-2, 2);
            value = max(1, min(100, value));
        } else {
            value = rnd.any(candidates);
        }
        candidates.push_back(value);
    }

    shuffle(candidates.begin(), candidates.end());

    int t = rnd.next(1, min(100, (int)candidates.size()));
    println(t);
    for (int i = 0; i < t; ++i) {
        println(candidates[i]);
    }

    return 0;
}
