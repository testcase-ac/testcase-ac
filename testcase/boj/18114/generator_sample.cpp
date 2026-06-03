#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int target = rnd.next(1, 200);
    vector<int> weights;
    set<int> used;

    auto addWeight = [&](int weight) {
        if (1 <= weight && weight <= 100000000 && !used.count(weight)) {
            used.insert(weight);
            weights.push_back(weight);
        }
    };

    if (mode == 0) {
        target = rnd.next(1, 100000000);
        addWeight(target);
    } else if (mode == 1) {
        int a = rnd.next(1, 50000000);
        int b = rnd.next(1, 50000000);
        while (a == b) b = rnd.next(1, 50000000);
        target = a + b;
        addWeight(a);
        addWeight(b);
    } else if (mode == 2) {
        int a = rnd.next(1, 300);
        int b = rnd.next(301, 700);
        int c = rnd.next(701, 1200);
        target = a + b + c;
        addWeight(a);
        addWeight(b);
        addWeight(c);
    } else if (mode == 3) {
        target = rnd.next(1, 1000);
        int base = rnd.next(target + 1, target + 500);
        int n = rnd.next(1, 18);
        for (int i = 0; i < n; ++i) addWeight(base + i);
    } else if (mode == 4) {
        target = rnd.next(10, 80);
        int n = rnd.next(6, 24);
        while ((int)weights.size() < n) addWeight(rnd.next(1, 120));
    } else {
        target = rnd.next(99999970, 100000000);
        addWeight(100000000);
        addWeight(99999999);
        addWeight(99999998);
    }

    int desiredN = rnd.next(max(1, (int)weights.size()), 28);
    while ((int)weights.size() < desiredN) {
        if (mode == 3) {
            addWeight(rnd.next(target + 1, min(100000000, target + 10000)));
        } else if (mode == 5) {
            addWeight(rnd.next(99990000, 100000000));
        } else {
            addWeight(rnd.next(1, 100000000));
        }
    }

    shuffle(weights.begin(), weights.end());
    println((int)weights.size(), target);
    println(weights);

    return 0;
}
