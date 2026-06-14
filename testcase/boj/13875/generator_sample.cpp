#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000000;
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(2, 20);
    } else if (mode == 1) {
        vector<int> anchors = {3, 12, 97, 100, 997, 1000};
        int base = rnd.any(anchors);
        n = base + rnd.next(-2, 2);
    } else if (mode == 2) {
        int p = rnd.any(vector<int>{29, 31, 37, 41, 43, 47, 53, 59, 61});
        n = p + rnd.next(0, 5);
    } else if (mode == 3) {
        int power = rnd.any(vector<int>{100, 1000, 10000, 100000, 1000000});
        n = power + rnd.next(-10, 10);
    } else if (mode == 4) {
        n = maxN - rnd.next(0, 1000);
    } else {
        n = rnd.next(2, maxN);
    }

    n = max(2, min(maxN, n));
    println(n);
    return 0;
}
