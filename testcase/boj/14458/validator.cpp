#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read left side permutation
    vector<char> seen(N+1, 0);
    for (int i = 1; i <= N; i++) {
        int x = inf.readInt(1, N, "left_i");
        inf.readEoln();
        ensuref(!seen[x],
                "Duplicate species %d on left side at position %d", x, i);
        seen[x] = 1;
    }
    // Ensure it's a full permutation
    for (int x = 1; x <= N; x++) {
        ensuref(seen[x],
                "Missing species %d on left side", x);
    }

    // Read right side permutation
    fill(seen.begin(), seen.end(), 0);
    for (int i = 1; i <= N; i++) {
        int x = inf.readInt(1, N, "right_i");
        inf.readEoln();
        ensuref(!seen[x],
                "Duplicate species %d on right side at position %d", x, i);
        seen[x] = 1;
    }
    // Ensure it's a full permutation
    for (int x = 1; x <= N; x++) {
        ensuref(seen[x],
                "Missing species %d on right side", x);
    }

    // No extra data
    inf.readEof();
    return 0;
}
