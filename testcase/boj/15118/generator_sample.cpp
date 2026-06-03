#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000000;
    int mode = rnd.next(0, 7);
    int n;

    if (mode == 0) {
        n = rnd.next(2, 20);
    } else if (mode == 1) {
        vector<int> anchors = {2, 3, 4, 5, 7, 10, 1919};
        n = anchors[rnd.next((int)anchors.size())];
        n += rnd.next(-1, 1);
        n = max(2, n);
    } else if (mode == 2) {
        int base = rnd.next(20, 1000);
        n = base + rnd.next(-2, 2);
    } else if (mode == 3) {
        vector<int> powers = {32, 64, 128, 256, 512, 1024, 4096, 32768, 1048576};
        n = powers[rnd.next((int)powers.size())] + rnd.next(-3, 3);
    } else if (mode == 4) {
        n = rnd.next(100000, 10000000);
    } else if (mode == 5) {
        n = maxN - rnd.next(0, 1000);
    } else {
        n = rnd.next(2, maxN);
    }

    n = min(max(n, 2), maxN);
    println(n);
    return 0;
}
