#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t;
    vector<int> ns;

    if (mode == 0) {
        t = rnd.next(1, 12);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(1, 10));
    } else if (mode == 1) {
        t = rnd.next(5, 25);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(1, 200));
    } else if (mode == 2) {
        t = rnd.next(8, 35);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(90000, 100000));
    } else if (mode == 3) {
        vector<int> anchors = {1, 2, 3, 4, 5, 9, 10, 11, 99, 100, 101,
                               999, 1000, 1001, 9999, 10000, 10001,
                               99999, 100000};
        t = rnd.next(6, 40);
        for (int i = 0; i < t; ++i) {
            int value = rnd.any(anchors);
            int delta = rnd.next(-2, 2);
            ns.push_back(max(1, min(100000, value + delta)));
        }
    } else if (mode == 4) {
        t = rnd.next(20, 100);
        int base = rnd.next(1, 100000);
        int radius = rnd.next(0, 500);
        for (int i = 0; i < t; ++i) {
            int value = base + rnd.next(-radius, radius);
            ns.push_back(max(1, min(100000, value)));
        }
    } else {
        t = rnd.next(1, 100);
        for (int i = 0; i < t; ++i) {
            int bias = rnd.next(0, 3);
            if (bias == 0) ns.push_back(rnd.next(1, 100));
            else if (bias == 1) ns.push_back(rnd.next(100, 10000));
            else if (bias == 2) ns.push_back(rnd.next(10000, 100000));
            else ns.push_back(rnd.next(1, 100000));
        }
    }

    println(t);
    for (int n : ns) println(n);

    return 0;
}
