#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // N from 5 to 30, biased towards small
    int N = rnd.wnext(26, -1) + 5;
    vector<int> arr(N);
    iota(arr.begin(), arr.end(), 1);

    // Apply three random reversals with varied segment sizes
    for (int k = 0; k < 3; k++) {
        int mode = rnd.next(0, 2);
        int i, j, len;
        if (mode == 0) {
            // small segment
            int maxSmall = min(5, N);
            len = rnd.next(1, maxSmall);
            i = rnd.next(1, N - len + 1);
            j = i + len - 1;
        } else if (mode == 1) {
            // large segment
            int minLarge = max(1, N - 5);
            len = rnd.next(minLarge, N);
            i = rnd.next(1, N - len + 1);
            j = i + len - 1;
        } else {
            // uniform random segment
            i = rnd.next(1, N);
            j = rnd.next(i, N);
        }
        reverse(arr.begin() + i - 1, arr.begin() + j);
    }

    // Output the test case
    println(N);
    println(arr);
    return 0;
}
