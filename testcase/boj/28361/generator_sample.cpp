#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int minN = 5;
    const int maxN = 1000000;
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = minN + rnd.next(0, 5);
    } else if (mode == 1) {
        int residue = rnd.next(0, 2);
        int base = rnd.next(2, 30) * 3 + residue;
        n = max(minN, base);
    } else if (mode == 2) {
        n = rnd.next(20, 200);
    } else if (mode == 3) {
        n = rnd.next(1000, 20000);
    } else if (mode == 4) {
        int residue = rnd.next(0, 2);
        int k = rnd.next(1, 1000);
        n = maxN - k;
        n -= ((n % 3 - residue) + 3) % 3;
        n = max(minN, n);
    } else {
        vector<int> edges = {5, 6, 7, 8, 9, 999999, 1000000};
        n = rnd.any(edges);
    }

    println(n);
    return 0;
}
