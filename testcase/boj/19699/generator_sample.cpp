#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;
    vector<int> h;

    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, n);
        int upper = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) h.push_back(rnd.next(1, upper));
    } else if (mode == 1) {
        n = rnd.next(4, 9);
        m = rnd.next(1, n);
        int base = rnd.next(1, 40);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(0, 3);
            h.push_back(min(1000, base + delta));
        }
    } else if (mode == 2) {
        n = rnd.next(5, 9);
        m = rnd.next(2, n);
        for (int i = 0; i < n; ++i) h.push_back(2 * rnd.next(1, 250));
        if (rnd.next(0, 1)) h[rnd.next(0, n - 1)] = rnd.next(1, 1000);
    } else if (mode == 3) {
        n = rnd.next(6, 9);
        m = rnd.next(1, n);
        for (int i = 0; i < n; ++i) h.push_back(rnd.next(1, 60));
    } else if (mode == 4) {
        n = rnd.next(6, 9);
        m = rnd.next(max(1, n - 3), n);
        for (int i = 0; i < n; ++i) h.push_back(rnd.next(900, 1000));
    } else {
        n = 9;
        m = rnd.next(1, 9);
        for (int i = 0; i < n; ++i) h.push_back(rnd.next(1, 1000));
    }

    shuffle(h.begin(), h.end());

    println(n, m);
    println(h);

    return 0;
}
