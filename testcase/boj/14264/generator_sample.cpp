#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int L;

    if (mode == 0) {
        vector<int> edges = {1, 2, 3, 5, 10, 100000, 1000000};
        L = rnd.any(edges);
    } else if (mode == 1) {
        L = rnd.next(1, 20);
    } else if (mode == 2) {
        int base = rnd.any(vector<int>{10, 100, 1000, 10000, 100000});
        L = max(1, min(1000000, base + rnd.next(-9, 9)));
    } else if (mode == 3) {
        L = rnd.next(999900, 1000000);
    } else if (mode == 4) {
        L = rnd.next(1, 1000000);
    } else {
        int x = rnd.next(1, 1000);
        L = x * x;
    }

    println(L);
    return 0;
}
