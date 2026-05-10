#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read K: number of chapters/files
        int K = inf.readInt(3, 1000000, "K");
        inf.readEoln();

        // Read K file sizes
        vector<int> sizes = inf.readInts(K, 1, 10000, "file_size");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
