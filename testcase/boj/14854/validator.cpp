#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test case: N and K
    for (int tc = 0; tc < T; ++tc) {
        // 1 ≤ N ≤ 1e9
        long long N = inf.readLong(1LL, 1000000000LL, "N");
        inf.readSpace();
        // 0 ≤ K ≤ N
        long long K = inf.readLong(0LL, N, "K");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
