#include "testlib.h"
#include <vector>
#include <set>
#include <limits>
using namespace std;

// Reads one solution block (an integer value + N numbers) from the given stream.
// Checks that the N numbers are distinct and in [1, 1e9], computes the number
// of distinct absolute differences among them, and returns that count.
// On any format error or violation, calls stream.quitf(_wa, ...) if stream == ouf,
// or stream.quitf(_fail, ...) if stream == ans.
int readSolution(InStream &stream, int N) {
    // Read the claimed value (we'll ignore it for computation; result is computed)
    stream.readInt(0, N*(N-1)/2, "claimed distinct count");
    // Read the N numbers
    vector<int> a(N);
    vector<bool> seen(N, false);
    set<int> used;
    for (int i = 0; i < N; i++) {
        a[i] = stream.readInt(1, 1000000000, format("a[%d]", i+1).c_str());
        if (used.count(a[i])) {
            stream.quitf(_wa, "number %d is used twice", a[i]);
        }
        used.insert(a[i]);
    }
    // Compute distinct absolute differences
    set<int> diffs;
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            int d = a[i] > a[j] ? a[i] - a[j] : a[j] - a[i];
            diffs.insert(d);
        }
    }
    return (int)diffs.size();
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int N = inf.readInt(2, 30, "N");
    // Read jury answer
    int j_max = readSolution(ans, N);
    int j_min = readSolution(ans, N);
    // Read participant output
    int p_max = readSolution(ouf, N);
    int p_min = readSolution(ouf, N);
    // No extra tokens
    ouf.readEof();

    // Check max-distinct
    if (j_max > p_max) {
        quitf(_wa, "max distinct is too small: jury = %d, found = %d", j_max, p_max);
    }
    if (j_max < p_max) {
        quitf(_fail, "participant found better max distinct than jury: jury = %d, found = %d", j_max, p_max);
    }
    // Check min-distinct (smaller is better)
    if (j_min < p_min) {
        quitf(_wa, "min distinct is too large: jury = %d, found = %d", j_min, p_min);
    }
    if (j_min > p_min) {
        quitf(_fail, "participant found better min distinct than jury: jury = %d, found = %d", j_min, p_min);
    }
    // Both optimal
    quitf(_ok, "max = %d, min = %d", p_max, p_min);
    return 0;
}
