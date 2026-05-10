#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases, assume 1 <= T <= 100000 by default
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; tc++) {
        // Each PS string has length between 2 and 50, only '(' or ')'
        inf.readToken("[()]{2,50}", "s");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
