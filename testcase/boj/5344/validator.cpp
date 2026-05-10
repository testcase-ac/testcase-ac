#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of problem sets
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        setTestCase(i + 1);

        // Two positive integers, separated by one or more spaces
        int a = inf.readInt(1, 2147483647, "a"); // int max, as problem doesn't specify upper bound
        inf.readSpace();
        int b = inf.readInt(1, 2147483647, "b");
        inf.readEoln();
    }

    inf.readEof();
}
