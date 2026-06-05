#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<int> ns;

    auto add = [&](int n) {
        ns.push_back(n);
    };

    if (mode == 0) {
        int t = rnd.next(1, 12);
        for (int i = 0; i < t; ++i) {
            add(rnd.next(1, 20));
        }
    } else if (mode == 1) {
        int t = rnd.next(3, 18);
        int residue = rnd.next(0, 2);
        for (int i = 0; i < t; ++i) {
            int q = rnd.next(0, 40);
            int n = 3 * q + residue;
            if (n < 1) n += 3;
            add(n);
        }
    } else if (mode == 2) {
        int t = rnd.next(5, 25);
        for (int i = 0; i < t; ++i) {
            int base = rnd.next(1, 3333) * 3;
            int delta = rnd.next(-2, 2);
            int n = base + delta;
            if (n < 1) n = 1;
            if (n > 10000) n = 10000;
            add(n);
        }
    } else if (mode == 3) {
        int t = rnd.next(4, 20);
        for (int i = 0; i < t; ++i) {
            add(rnd.next(9900, 10000));
        }
    } else {
        int t = rnd.next(20, 100);
        for (int i = 0; i < t; ++i) {
            if (rnd.next(0, 4) == 0) {
                add(rnd.any(vector<int>{1, 2, 3, 6, 9, 9999, 10000}));
            } else {
                add(rnd.next(1, 10000));
            }
        }
    }

    println((int)ns.size());
    for (int n : ns) {
        println(n);
    }

    return 0;
}
