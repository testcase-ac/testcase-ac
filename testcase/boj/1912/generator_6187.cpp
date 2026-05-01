#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose n between 1 and 20 for readability, sometimes edge n=1
    int n = rnd.next(1, 20);

    // Decide a pattern type to expose different cases
    int type = rnd.next(0, 3);

    vector<int> a(n);
    if (type == 0) {
        // All positives
        for (int i = 0; i < n; i++)
            a[i] = rnd.next(1, 1000);
    } else if (type == 1) {
        // All negatives
        for (int i = 0; i < n; i++)
            a[i] = -rnd.next(1, 1000);
    } else if (type == 2 && n >= 3) {
        // Positive prefix, one large negative, positive suffix
        int split = n / 2;
        for (int i = 0; i < split; i++)
            a[i] = rnd.next(1, 100);
        a[split] = -rnd.next(100, 1000);
        for (int i = split + 1; i < n; i++)
            a[i] = rnd.next(1, 100);
        // Force the suffix to beat the prefix sometimes
        if (rnd.next(0,1) == 0) {
            // boost last element
            a[n-1] = a[n-1] + rnd.next(100, 500);
        }
    } else {
        // Mixed uniform random
        for (int i = 0; i < n; i++)
            a[i] = rnd.next(-1000, 1000);
    }

    // Shuffle occasionally to avoid positional biases (but keep structure for type2)
    if (type != 2 && rnd.next(0,1)) {
        shuffle(a.begin(), a.end());
    }

    // Output
    println(n);
    println(a);

    return 0;
}
