#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: small or moderate n
    int n = (rnd.next(0,1) ? rnd.next(2,5) : rnd.next(6,15));

    // Hyper-parameter: value range size small or larger
    int maxVal;
    if (rnd.next(0,1)) {
        maxVal = rnd.next(n, n * 10);
    } else {
        maxVal = rnd.next(n * 10, n * 100);
    }

    // Build a unique array a of size n from [1..maxVal]
    vector<int> pool;
    for (int v = 1; v <= maxVal; ++v) pool.push_back(v);
    shuffle(pool.begin(), pool.end());
    vector<int> a(pool.begin(), pool.begin() + n);

    // Optionally sort the array to test ordered/unordered assumptions
    if (rnd.next(0,1)) {
        sort(a.begin(), a.end());
    } else {
        shuffle(a.begin(), a.end());
    }

    // Compute all pair sums
    vector<int> sums;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            sums.push_back(a[i] + a[j]);

    int minSum = *min_element(sums.begin(), sums.end());
    int maxSum = *max_element(sums.begin(), sums.end());

    // Decide whether to guarantee at least one solution
    bool hasSolution = rnd.next(0,1);
    int x;
    if (hasSolution) {
        // Pick x from one of the actual sums
        x = rnd.any(sums);
    } else {
        // Pick x outside the possible sums (greater than maxSum)
        x = maxSum + rnd.next(1, 10);
    }

    // Output the test case
    println(n);
    println(a);
    println(x);

    return 0;
}
