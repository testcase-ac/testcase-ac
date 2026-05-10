#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        long long n = inf.readLong(1LL, 1000000000000LL, "n"); // 1 <= n <= 1e12
        inf.readSpace();
        long long m = inf.readLong(1LL, 1000000000000LL, "m"); // 1 <= m <= 1e12
        inf.readEoln();

        // No additional global properties are specified that need validation.
        // The problem guarantees nothing like "answer always <= X" that must be checked.
        // Just basic range and format checks are sufficient.
    }

    inf.readEof();
}
