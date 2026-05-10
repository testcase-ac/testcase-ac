#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long total_K = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // 2. Read K
        int K = inf.readInt(3, 200000, "K");
        inf.readEoln();

        total_K += K;
        ensuref(total_K <= 200000, "Sum of K over all test cases exceeds 200000 (now %lld at test case %d)", total_K, tc);

        // 3. Read file sizes
        vector<int> sizes = inf.readInts(K, 1, 10000, "file_size");
        inf.readEoln();

        // No further global constraints to check for this problem
    }

    inf.readEof();
}
