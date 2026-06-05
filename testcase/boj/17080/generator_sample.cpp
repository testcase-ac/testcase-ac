#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 5000000;
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        vector<int> edges = {1, 2, 3, 4, 5, 6, 7, 8, maxN - 3, maxN - 2, maxN - 1, maxN};
        n = rnd.any(edges);
    } else if (mode == 1) {
        int residue = rnd.next(0, 3);
        int base = rnd.next(0, 25) * 4;
        n = base + residue + 1;
    } else if (mode == 2) {
        int residue = rnd.next(0, 3);
        int base = rnd.next(1000, 300000) * 4;
        n = base + residue + 1;
    } else if (mode == 3) {
        n = rnd.next(1, 100);
    } else if (mode == 4) {
        n = rnd.next(101, 100000);
    } else {
        n = rnd.next(100001, maxN);
    }

    println(n);
    return 0;
}
