#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 20);
    int mode = rnd.next(0, 3);
    int startParity = rnd.next(0, 1);
    int runLength = rnd.next(1, 5);
    vector<int> a(n);

    for (int i = 0; i < n; ++i) {
        int parity = mode == 0 ? startParity
                   : mode == 1 ? startParity ^ (i % 2)
                   : mode == 2 ? rnd.next(0, 1)
                               : startParity ^ ((i / runLength) % 2);
        a[i] = parity ? rnd.next(0, 49999) * 2 + 1
                      : rnd.next(1, 50000) * 2;
    }

    println(n);
    println(a);
}
