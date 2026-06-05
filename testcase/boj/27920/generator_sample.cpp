#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> edges = {1, 2, 3, 4, 5, 199999, 200000};
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.any(edges);
    } else if (mode == 1) {
        n = rnd.next(1, 20);
    } else if (mode == 2) {
        int k = rnd.next(1, 17);
        n = (1 << k) + rnd.next(-2, 2);
        n = max(1, min(200000, n));
    } else if (mode == 3) {
        n = 2 * rnd.next(1, 100000);
    } else if (mode == 4) {
        n = 2 * rnd.next(0, 99999) + 1;
    } else {
        n = rnd.next(1, 200000);
    }

    println(n);
    return 0;
}
