#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose small N
    int N = rnd.next(2, 10);
    // Hyper-parameter: value range small or large
    bool smallRange = rnd.next(0, 1) == 0;
    int maxVal = smallRange ? rnd.next(10, 20) : rnd.next(100000, 100000000);
    // Prepare array
    vector<int> a(N);
    // Hyper-parameter: sequence pattern
    int pattern = rnd.next(0, 3);
    if (pattern == 0) {
        // Pure random
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(1, maxVal);
    } else if (pattern == 1) {
        // Sorted ascending random
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(1, maxVal);
        sort(a.begin(), a.end());
    } else if (pattern == 2) {
        // Sorted descending random
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(1, maxVal);
        sort(a.begin(), a.end(), greater<int>());
    } else {
        // Few distinct values
        int K = rnd.next(1, min(N, 3));
        vector<int> vals(K);
        for (int i = 0; i < K; i++)
            vals[i] = rnd.next(1, maxVal);
        for (int i = 0; i < N; i++)
            a[i] = rnd.any(vals);
        // Maybe shuffle duplicates
        if (rnd.next(0,1)) shuffle(a.begin(), a.end());
    }
    // Possibly introduce a single big spike or dip
    if (rnd.next(0.0, 1.0) < 0.3) {
        int pos = rnd.next(0, N-1);
        // Either very small or very large
        if (rnd.next(0,1))
            a[pos] = 1;
        else
            a[pos] = maxVal;
    }
    // Output
    println(N);
    for (int x : a) println(x);
    return 0;
}
