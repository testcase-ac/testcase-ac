#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of games T
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // Each line: single integer N, number of stations in the line
        long long N = inf.readLong(1LL, 1000000000LL, "N");
        inf.readEoln();

        // No additional global properties guaranteed in statement,
        // so nothing more to validate for each test.
    }

    inf.readEof();
}
