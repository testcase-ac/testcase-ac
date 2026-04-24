#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    // M can be extremely large, read as string of digits
    string M = inf.readToken("[0-9]+", "M");
    inf.readEoln();

    // Validate M: 1 <= M <= 10^200000
    // No leading zeros allowed (since M >= 1)
    ensuref(M[0] != '0',
            "M has leading zero");
    int lenM = (int)M.size();
    // The maximum allowed value is 10^200000 which is "1" + 200000 zeros => length 200001
    ensuref(lenM <= 200001,
            "length of M (%d) exceeds maximum allowed 200001", lenM);
    if (lenM == 200001) {
        // Must be exactly '1' followed by 200000 '0's
        ensuref(M[0] == '1',
                "when length of M is %d, first character must be '1', found '%c'",
                lenM, M[0]);
        for (int i = 1; i < lenM; i++) {
            ensuref(M[i] == '0',
                    "when length of M is %d, character at position %d must be '0', found '%c'",
                    lenM, i+1, M[i]);
        }
    }
    // If length < 200001, any value from 1 to (10^200000 -1) is allowed

    // Read the permutation A of size n
    vector<int> A = inf.readInts(n, 1, n, "A");
    inf.readEoln();

    // Validate that A is a permutation: no duplicates
    vector<char> seen(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int ai = A[i];
        ensuref(!seen[ai],
                "Duplicate element in A at position %d: %d", i+1, ai);
        seen[ai] = 1;
    }

    inf.readEof();
    return 0;
}
