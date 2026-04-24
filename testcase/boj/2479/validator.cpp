#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(3, 1000, "N");
    inf.readSpace();
    int K = inf.readInt(2, 30, "K");
    inf.readEoln();

    // Read N distinct binary codes of length K
    set<string> codes;
    for (int i = 1; i <= N; i++) {
        // Read a token of 0/1 characters
        string s = inf.readToken("[01]+", "code");
        // Check exact length
        ensuref((int)s.size() == K,
                "code %d has length %d but expected %d", i, (int)s.size(), K);
        // Characters are guaranteed by regex [01]+, but double‐check for safety
        for (char c : s) {
            ensuref(c == '0' || c == '1',
                    "code %d contains invalid character '%c'", i, c);
        }
        // Check uniqueness
        ensuref(codes.insert(s).second,
                "duplicate code at index %d: %s", i, s.c_str());
        inf.readEoln();
    }

    // Read the two distinct query indices A and B
    int A = inf.readInt(1, N, "A");
    inf.readSpace();
    int B = inf.readInt(1, N, "B");
    ensuref(A != B, "start and end indices must differ but both are %d", A);
    inf.readEoln();

    // No further global constraints to check (connectivity not guaranteed)
    inf.readEof();
    return 0;
}
