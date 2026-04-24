#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases: assume 1 ≤ n ≤ 100000 as per unspecified limit rule
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Each test case: a non-empty line of at most 18 characters (any characters except newline)
    for (int i = 0; i < n; i++) {
        // [^] matches any character; {1,18} enforces length between 1 and 18 inclusive
        inf.readLine("[^]{1,18}", "s");
    }

    inf.readEof();
    return 0;
}
