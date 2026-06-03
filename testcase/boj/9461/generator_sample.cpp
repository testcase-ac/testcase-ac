#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> ns;

    if (mode == 0) {
        int t = rnd.next(1, 10);
        int hi = rnd.next(t, 12);
        for (int i = 0; i < t; ++i) ns.push_back(hi - i);
    } else if (mode == 1) {
        int t = rnd.next(4, 18);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(1, 100));
    } else if (mode == 2) {
        int center = rnd.next(5, 100);
        int t = rnd.next(6, 20);
        for (int i = 0; i < t; ++i) {
            int delta = rnd.next(-5, 5);
            int n = max(1, min(100, center + delta));
            ns.push_back(n);
        }
    } else if (mode == 3) {
        int t = rnd.next(8, 25);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.any(vector<int>{1, 2, 3, 4, 5, 95, 96, 97, 98, 99, 100}));
    } else if (mode == 4) {
        int t = rnd.next(10, 30);
        for (int i = 0; i < t; ++i) {
            int block = rnd.next(0, 9);
            ns.push_back(rnd.next(block * 10 + 1, block * 10 + 10));
        }
    } else {
        int t = rnd.next(30, 80);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(1, 100));
    }

    shuffle(ns.begin(), ns.end());

    println((int)ns.size());
    for (int n : ns) println(n);

    return 0;
}
