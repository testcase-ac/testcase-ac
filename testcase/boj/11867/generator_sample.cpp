#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> anchors = {
        {1, 2}, {2, 1}, {1, 100}, {100, 1},
        {99, 99}, {100, 100}, {2, 2}, {3, 4},
    };

    int n, m;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        auto p = rnd.any(anchors);
        n = p.first;
        m = p.second;
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
    } else if (mode == 2) {
        int nParity = rnd.next(0, 1);
        int mParity = rnd.next(0, 1);
        n = 1 + 2 * rnd.next(0, 49);
        m = 1 + 2 * rnd.next(0, 49);
        if (nParity == 0) n = rnd.next(1, 50) * 2;
        if (mParity == 0) m = rnd.next(1, 50) * 2;
    } else {
        n = rnd.next(1, 100);
        m = rnd.next(1, 100);
    }

    if (n == 1 && m == 1) {
        if (rnd.next(0, 1) == 0) n = 2;
        else m = 2;
    }

    if (rnd.next(0, 1) == 0) swap(n, m);

    println(n, m);
    return 0;
}
