#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(2, 6);
        int value = rnd.next(1, 999);
        a.assign(n, value);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int lo = rnd.next(1, 50);
        int hi = rnd.next(950, 999);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, 1) == 0 ? rnd.next(1, lo) : rnd.next(hi, 999));
        }
    } else if (mode == 2) {
        vector<int> patterns = {1, 9, 10, 11, 19, 99, 100, 101, 109, 111, 119, 199, 909, 990, 999};
        n = rnd.next(2, 15);
        for (int i = 0; i < n; ++i) {
            a.push_back(patterns[rnd.next((int)patterns.size())]);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(900, 999));
        }
    } else if (mode == 4) {
        n = rnd.next(2, 40);
        int upper = rnd.next(2, 999);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, upper));
        }
    } else {
        n = rnd.next(50, 120);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 999));
        }
    }

    shuffle(a.begin(), a.end());
    println(n);
    println(a);

    return 0;
}
