#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: total number of fireworks, integer between 3 and 10101 inclusive.
    int N = inf.readInt(3, 10101, "N");
    inf.readEoln();

    // Globally ensure that there exists an integer K >= 1 such that 1 + K + K^2 == N.
    bool found = false;
    for (int K = 1; ; K++) {
        long long total = 1LL + K + 1LL * K * K;
        if (total == N) {
            found = true;
            break;
        }
        if (total > N) {
            break;
        }
    }
    ensuref(found, "No integer K satisfies 1 + K + K^2 = %d", N);

    inf.readEof();
    return 0;
}
