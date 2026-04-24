#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; tc++) {
        setTestCase(tc);

        // n: length of the sequence
        int n = inf.readInt(2, 1000, "n");
        inf.readEoln();

        // Sequence a of length n, each element is 1 or 2
        vector<int> a = inf.readInts(n, 1, 2, "a_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
