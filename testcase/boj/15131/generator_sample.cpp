#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000;
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(2, 30);
    } else if (mode == 1) {
        vector<int> anchors = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 17, 20};
        n = rnd.any(anchors) + rnd.next(0, 3);
    } else if (mode == 2) {
        int divisor = rnd.any(vector<int>{2, 3, 4, 5, 6, 7});
        int quotient = rnd.next(1, 5000);
        int residue = rnd.next(0, divisor - 1);
        n = divisor * quotient + residue;
    } else if (mode == 3) {
        int base = rnd.next(1000, 100000);
        n = base + rnd.next(-20, 20);
    } else if (mode == 4) {
        n = maxN - rnd.next(0, 2000);
    } else {
        n = rnd.next(2, maxN);
    }

    n = max(2, min(maxN, n));
    println(n);
    return 0;
}
