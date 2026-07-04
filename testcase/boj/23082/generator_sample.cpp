#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int LIMIT = 1000000000;
    vector<int> powers;
    for (int x = 1; x <= LIMIT / 3; x *= 3) {
        powers.push_back(x);
    }
    powers.push_back(1162261467 / 3);

    int mode = rnd.next(0, 5);
    int n = 0;

    if (mode == 0) {
        n = 0;
    } else if (mode == 1) {
        n = rnd.any(vector<int>{-LIMIT, -LIMIT + 1, -1, 1, LIMIT - 1, LIMIT});
    } else if (mode == 2) {
        n = rnd.any(powers);
        if (rnd.next(0, 1)) n = -n;
    } else if (mode == 3) {
        int base = rnd.any(powers);
        int delta = rnd.any(vector<int>{-2, -1, 1, 2});
        if (base + delta > LIMIT) delta = -delta;
        n = base + delta;
        if (rnd.next(0, 1)) n = -n;
    } else if (mode == 4) {
        int magnitude = rnd.next(1, 5000);
        n = rnd.next(0, 1) ? magnitude : -magnitude;
    } else {
        n = rnd.next(-LIMIT, LIMIT);
    }

    println(n);
    return 0;
}
