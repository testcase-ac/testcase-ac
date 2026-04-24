#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_CASES = 100000;
    const int MIN_N = 2;
    const int MAX_N = 1000000;
    int tc = 0;
    while (true) {
        // Read N, accept 0 as terminator
        int N = inf.readInt(0, MAX_N, "N");
        inf.readEoln();
        if (N == 0) {
            break;
        }
        // Now a real test case
        ++tc;
        setTestCase(tc);
        ensuref(tc <= MAX_CASES,
                "Number of test cases %d exceeds limit %d", tc, MAX_CASES);
        ensuref(N >= MIN_N,
                "N = %d is too small; must be at least %d", N, MIN_N);

        // Read the string S of length N
        // We read the full line (excluding EOL), then check its length and chars
        string S = inf.readLine("[^]+", "S");
        ensuref((int)S.size() == N,
                "Length of S (%d) does not match N (%d)", (int)S.size(), N);
        for (int i = 0; i < N; i++) {
            unsigned char c = S[i];
            ensuref(c >= 97 && c <= 126,
                    "Invalid character code %d at position %d in S; must be in [97,126]",
                    c, i+1);
        }
    }

    inf.readEof();
    return 0;
}
