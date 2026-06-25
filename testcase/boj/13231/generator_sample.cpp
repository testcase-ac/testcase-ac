#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> ns;

    if (mode == 0) {
        int t = rnd.next(1, 8);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(1, 10));
    } else if (mode == 1) {
        int t = rnd.next(5, 20);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(1, 80));
    } else if (mode == 2) {
        int t = rnd.next(5, 20);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(400, 500));
    } else if (mode == 3) {
        int t = rnd.next(10, 30);
        int base = rnd.next(1, 500);
        for (int i = 0; i < t; ++i) ns.push_back(max(1, min(500, base + rnd.next(-3, 3))));
    } else if (mode == 4) {
        ns = {1, 2, 3, 7, 9, 10, 50, 99, 100, 499, 500};
        shuffle(ns.begin(), ns.end());
        ns.resize(rnd.next(4, int(ns.size())));
    } else {
        int t = rnd.next(50, 100);
        for (int i = 0; i < t; ++i) {
            if (rnd.next(0, 3) == 0)
                ns.push_back(rnd.next(450, 500));
            else
                ns.push_back(rnd.next(1, 500));
        }
    }

    println(int(ns.size()));
    for (int n : ns) println(n);

    return 0;
}
