#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    vector<int> ns;

    if (mode == 0) {
        ns.push_back(rnd.any(vector<int>{1, 2, 3, 999, 1000}));
    } else if (mode == 1) {
        int t = rnd.next(1, 12);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(1, 20));
    } else if (mode == 2) {
        int t = rnd.next(1, 20);
        int lo = rnd.next(1, 900);
        int hi = rnd.next(lo, 1000);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(lo, hi));
    } else if (mode == 3) {
        int t = rnd.next(50, 100);
        for (int i = 0; i < t; ++i) {
            ns.push_back(rnd.any(vector<int>{1, 2, 999, 1000}));
        }
    } else if (mode == 4) {
        int t = rnd.next(5, 30);
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(1, 500) * 2;
            if (rnd.next(0, 1)) --n;
            ns.push_back(n);
        }
    } else {
        int t = rnd.next(10, 100);
        for (int i = 0; i < t; ++i) ns.push_back(rnd.next(1, 1000));
    }

    println((int)ns.size());
    for (int n : ns) println(n);

    return 0;
}
