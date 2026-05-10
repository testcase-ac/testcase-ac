#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    // Read sequence a_1..a_n, each on its own line
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readInt(-10000, 10000, "a_i");
        inf.readEoln();
    }

    // No global conditions like "answer always exists" beyond k<=n,
    // which is already enforced. Still, we can safely compute the
    // maximum sum to check for overflow-related issues in generators.
    // Use 64-bit to avoid overflow in sums.
    long long windowSum = 0;
    for (int i = 0; i < k; ++i) windowSum += a[i];
    long long best = windowSum;
    for (int i = k; i < n; ++i) {
        windowSum += a[i];
        windowSum -= a[i - k];
        if (windowSum > best) best = windowSum;
    }
    // No constraints on best to check, but computing ensures k<=n was meaningful.

    inf.readEof();
}
