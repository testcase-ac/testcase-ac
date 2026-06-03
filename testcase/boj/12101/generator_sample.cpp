#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> ways(11);
    ways[0] = 1;
    for (int n = 1; n <= 10; ++n) {
        for (int add = 1; add <= 3; ++add) {
            if (n >= add) ways[n] += ways[n - add];
        }
    }

    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 3);
        k = rnd.next(1, ways[n]);
    } else if (mode == 1) {
        n = rnd.next(8, 10);
        k = rnd.next(1, ways[n]);
    } else if (mode == 2) {
        n = rnd.next(1, 10);
        k = max(1, ways[n] - rnd.next(0, min(ways[n] - 1, 5)));
    } else if (mode == 3) {
        n = rnd.next(1, 10);
        k = ways[n] + rnd.next(1, 20);
    } else if (mode == 4) {
        n = rnd.next(1, 10);
        k = rnd.next(1000000000, 2147483647);
    } else {
        n = rnd.next(1, 10);
        k = rnd.next(1, 2147483647);
    }

    println(n, k);
    return 0;
}
