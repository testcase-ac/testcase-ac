#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        // n is a positive integer, n <= 1000
        int n = inf.readInt(1, 1000, "n");
        inf.readEoln();
    }

    // No extra whitespace after last test line
    inf.readEof();
}
