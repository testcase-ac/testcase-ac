#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small size
    int n = rnd.next(3, 20);
    int k = rnd.next(3, n);

    vector<int> a(n);
    // Hyper-parameter: pattern for first k-1 elements
    int pattern = rnd.next(0, 3);
    if (pattern == 0) {
        // Random small positives
        for (int i = 0; i < k - 1; i++)
            a[i] = rnd.next(1, 20);
    } else if (pattern == 1) {
        // All equal
        int v = rnd.next(1, 20);
        for (int i = 0; i < k - 1; i++)
            a[i] = v;
    } else if (pattern == 2) {
        // Increasing sequence
        for (int i = 0; i < k - 1; i++)
            a[i] = i + 1;
    } else {
        // Random mix of zero and positive
        for (int i = 0; i < k - 1; i++)
            a[i] = rnd.next(0, 1) ? rnd.next(1, 50) : 0;
    }
    // Tail zeros to guarantee a valid split: use k-1 singletons and tail as one segment
    for (int i = k - 1; i < n; i++)
        a[i] = 0;

    // Output
    println(n, k);
    println(a);

    return 0;
}
