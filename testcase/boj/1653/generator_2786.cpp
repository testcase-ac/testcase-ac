#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for n: sometimes small, sometimes larger
    bool smallN = rnd.next(0, 1);
    int n = smallN ? rnd.next(1, 4) : rnd.next(5, 9);

    // Generate distinct weights from 1..9
    vector<int> w(9);
    iota(w.begin(), w.end(), 1);
    shuffle(w.begin(), w.end());
    w.resize(n);
    sort(w.begin(), w.end());

    // Hyper-parameter for k: sometimes small, sometimes very large
    bool largeK = rnd.next(0, 1);
    int k;
    if (largeK) {
        // k in upper range to test fallback behavior
        k = rnd.next(1000000, 1000000000);
    } else {
        // k in small to moderate range
        k = rnd.next(0, 5000);
    }

    // Output
    println(n);
    println(w);
    println(k);

    return 0;
}
