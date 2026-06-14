#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampN(int value) {
    return max(1, min(1000000, value));
}

int randomDistinctVolume() {
    int a = rnd.next(1, 100);
    int b = rnd.next(a + 1, 1000);
    int maxC = 1000000 / (a * b);
    if (maxC <= b) return rnd.next(1, 1000000);
    int c = rnd.next(b + 1, maxC);
    return a * b * c;
}

int nearInterestingVolume() {
    int base = randomDistinctVolume();
    return clampN(base + rnd.next(-3, 3));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t;
    if (mode == 5) {
        t = rnd.next(200, 1000);
    } else {
        t = rnd.next(8, 40);
    }

    vector<int> ns;
    ns.reserve(t);

    vector<int> anchors = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        29, 30, 31, 665, 666, 667,
        999997, 999998, 999999, 1000000
    };
    shuffle(anchors.begin(), anchors.end());

    for (int value : anchors) {
        if ((int)ns.size() == t) break;
        ns.push_back(value);
    }

    while ((int)ns.size() < t) {
        int n;
        if (mode == 0) {
            n = rnd.next(1, 80);
        } else if (mode == 1) {
            n = nearInterestingVolume();
        } else if (mode == 2) {
            n = rnd.next(1, 2000);
        } else if (mode == 3) {
            n = 1000000 - rnd.wnext(100000, 2);
        } else if (mode == 4) {
            n = rnd.next(1, 1000000);
        } else {
            n = rnd.next(1, 1000000);
        }
        ns.push_back(clampN(n));
    }

    shuffle(ns.begin(), ns.end());

    println(t);
    for (int n : ns) println(n);

    return 0;
}
