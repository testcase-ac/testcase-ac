#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_N = 1000000000;
    vector<int> digitBoundaries = {
        9, 10, 11,
        99, 100, 101,
        999, 1000, 1001,
        9999, 10000, 10001,
        99999, 100000, 100001,
        999999, 1000000, 1000001,
        9999999, 10000000, 10000001,
        99999999, 100000000, 100000001,
        999999999, 1000000000
    };

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 30);
    } else if (mode == 1) {
        n = rnd.any(digitBoundaries);
    } else if (mode == 2) {
        int base = rnd.any(digitBoundaries);
        int delta = rnd.next(-25, 25);
        n = min(MAX_N, max(1, base + delta));
    } else if (mode == 3) {
        n = rnd.next(1, 1000000);
    } else {
        n = rnd.next(1, MAX_N);
    }

    println(n);
    return 0;
}
