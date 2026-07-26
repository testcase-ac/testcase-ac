#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int n = rnd.next(2, 12);
    const int treeMode = rnd.next(0, 2);
    const int densityMode = rnd.next(0, 3);
    const int lengthMode = rnd.next(0, 2);

    long long densityLow = 1, densityHigh = 30;
    if (densityMode == 0) {
        densityLow = densityHigh = rnd.next(1LL, 1000000000000000000LL);
    } else if (densityMode == 2) {
        densityLow = 999999999999999900LL;
        densityHigh = 1000000000000000000LL;
    } else if (densityMode == 3) {
        densityHigh = 1000000000000000000LL;
    }

    long long lengthLow = 1, lengthHigh = 30;
    if (lengthMode == 1) {
        lengthLow = 999999999900LL;
        lengthHigh = 1000000000000LL;
    } else if (lengthMode == 2) {
        lengthHigh = 1000000000000LL;
    }

    vector<long long> density(n);
    vector<int> parent(n - 1);
    vector<long long> length(n - 1);
    for (long long& value : density) {
        value = rnd.next(densityLow, densityHigh);
    }
    for (int j = 1; j < n; ++j) {
        parent[j - 1] = treeMode == 0 ? j + 1
                         : treeMode == 1 ? n
                                         : rnd.next(j + 1, n);
        length[j - 1] = rnd.next(lengthLow, lengthHigh);
    }

    println(n);
    println(density);
    println(parent);
    println(length);
}
