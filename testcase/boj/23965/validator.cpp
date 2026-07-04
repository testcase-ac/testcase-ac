#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCases = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= testCases; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(3, 5, "N");
        inf.readEoln();

        inf.readInts(3 * n, 1, 1000000, "A_i");
        inf.readEoln();

        inf.readInts(3 * n, 1, 1000000, "B_i");
        inf.readEoln();
    }

    inf.readEof();
}
