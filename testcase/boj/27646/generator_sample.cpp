#include "testlib.h"

#include <algorithm>
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int t = 0;
    std::vector<int> ns;

    if (mode == 0) {
        t = rnd.next(1, 5);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(1, 12));
    } else if (mode == 1) {
        t = rnd.next(3, 8);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(1, 1000));
    } else if (mode == 2) {
        ns = {1, 2, 3, 4, 999, 1000};
        shuffle(ns.begin(), ns.end());
        t = rnd.next(1, static_cast<int>(ns.size()));
        ns.resize(t);
    } else if (mode == 3) {
        t = rnd.next(4, 10);
        int start = rnd.next(1, 1000 - t + 1);
        for (int i = 0; i < t; ++i) ns.push_back(start + i);
    } else {
        t = rnd.next(10, 25);
        for (int i = 0; i < t; ++i) {
            if (rnd.next(0, 99) < 35) {
                ns.push_back(rnd.any(std::vector<int>{1, 2, 4, 35, 999, 1000}));
            } else {
                ns.push_back(rnd.next(1, 1000));
            }
        }
    }

    println(t);
    for (int n : ns) {
        printf("\n");
        println(n);
    }

    return 0;
}
