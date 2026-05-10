#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 1;
    const int N_MAX = 300000;
    const int A_MIN = 1;
    const int A_MAX = 100000000;

    int n = inf.readInt(N_MIN, N_MAX, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, A_MIN, A_MAX, "a_i");
    inf.readEoln();

    // Simulate to verify implied properties:
    // - number of segments (uses of the skill) is well-defined
    // - maximum length of a segment is within [1, n]
    long long segments = 0;
    int currentLen = 0;
    int maxLen = 0;

    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            segments = 1;
            currentLen = 1;
            maxLen = 1;
        } else {
            if (a[i] >= a[i - 1]) {
                currentLen++;
            } else {
                segments++;
                currentLen = 1;
            }
            if (currentLen > maxLen) maxLen = currentLen;
        }
    }

    ensuref(segments >= 1 && segments <= n,
            "Number of segments (%lld) must be between 1 and n=%d", segments, n);
    ensuref(maxLen >= 1 && maxLen <= n,
            "Maximum segment length (%d) must be between 1 and n=%d", maxLen, n);

    inf.readEof();
}
