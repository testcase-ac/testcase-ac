#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int clampN(int n) {
    return max(1, min(10000, n));
}

int nearValue(int center, int radius) {
    return clampN(center + rnd.next(-radius, radius));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> ns;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int t = rnd.next(1, 8);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(1, 20));
    } else if (mode == 1) {
        int t = rnd.next(4, 14);
        int base = rnd.next(1, 10000);
        for (int i = 0; i < t; ++i) ns.push_back(nearValue(base, 12));
    } else if (mode == 2) {
        int t = rnd.next(5, 16);
        int residue = rnd.next(0, 6);
        for (int i = 0; i < t; ++i) {
            int k = rnd.next(0, 1428);
            ns.push_back(clampN(7 * k + residue));
        }
    } else if (mode == 3) {
        vector<int> anchors = {1, 2, 3, 4, 7, 8, 9, 10, 14, 49, 50, 99, 100,
                               999, 1000, 9999, 10000};
        shuffle(anchors.begin(), anchors.end());
        int t = rnd.next(6, (int)anchors.size());
        for (int i = 0; i < t; ++i) ns.push_back(anchors[i]);
    } else if (mode == 4) {
        int t = rnd.next(3, 10);
        for (int i = 0; i < t; ++i) {
            int span = rnd.next(0, 200);
            ns.push_back(10000 - span);
        }
    } else {
        int t = rnd.next(10, 30);
        for (int i = 0; i < t; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) ns.push_back(rnd.next(1, 30));
            if (bucket == 1) ns.push_back(rnd.next(31, 300));
            if (bucket == 2) ns.push_back(rnd.next(301, 3000));
            if (bucket == 3) ns.push_back(rnd.next(3001, 10000));
        }
    }

    shuffle(ns.begin(), ns.end());

    println((int)ns.size());
    for (int n : ns) println(n);

    return 0;
}
