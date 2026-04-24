#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int tc = 1; tc <= N; tc++) {
        // Read a binary string token
        string s = inf.readToken("[01]+", "s");
        // Check length constraints
        int len = (int)s.size();
        ensuref(len < 1000,
                "Test case %d: string length must be < 1000, found %d",
                tc, len);
        ensuref(len % 2 == 0,
                "Test case %d: string length must be even, found %d",
                tc, len);
        ensuref(len >= 2,
                "Test case %d: string length must be at least 2, found %d",
                tc, len);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
