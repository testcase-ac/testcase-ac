#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 100);
    } else if (mode == 1) {
        n = rnd.next(1, 100);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    } else if (mode == 3) {
        int base = rnd.next(1, 100);
        n = max(1, min(100, base + rnd.next(-2, 2)));
        m = max(1, min(100, base + rnd.next(-2, 2)));
    } else if (mode == 4) {
        vector<int> edges = {1, 2, 3, 4, 5, 96, 97, 98, 99, 100};
        n = rnd.any(edges);
        m = rnd.any(edges);
    } else {
        n = rnd.next(1, 100);
        m = rnd.next(1, 100);
    }

    if (rnd.next(0, 1)) swap(n, m);

    println(n, m);
    return 0;
}
