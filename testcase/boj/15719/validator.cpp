#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 10000000, "N");
    inf.readEoln();

    // Prepare counter for values [0..N]
    vector<unsigned char> cnt(N+1, 0);

    // Read the sequence of N integers
    for (int i = 0; i < N; i++) {
        if (i > 0) {
            // Expect exactly one space between numbers
            inf.readSpace();
        }
        int x = inf.readInt(1, N-1, "A_i");
        // Count occurrences, but forbid more than 2
        cnt[x]++;
        ensuref(cnt[x] <= 2,
                "Value %d appears more than twice: %d times",
                x, cnt[x]);
    }
    inf.readEoln();

    // Validate that values 1..N-1 all appear at least once,
    // and that exactly one value appears twice.
    int duplicate_count = 0;
    for (int v = 1; v <= N-1; v++) {
        ensuref(cnt[v] > 0,
                "Value %d is missing from the sequence", v);
        if (cnt[v] == 2) {
            duplicate_count++;
        }
    }
    ensuref(duplicate_count == 1,
            "There must be exactly one duplicated value, found %d",
            duplicate_count);

    // Ensure that value 0 and N do not appear at all
    ensuref(cnt[0] == 0,
            "Invalid appearance of 0: count = %d", cnt[0]);
    ensuref(cnt[N] == 0,
            "Invalid appearance of %d: count = %d", N, cnt[N]);

    inf.readEof();
    return 0;
}
