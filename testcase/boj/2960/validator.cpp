#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K according to constraints:
    // 1 ≤ K < N, max(1, K) < N ≤ 1000
    // This implies N >= 2, N <= 1000, and 1 <= K <= N-1.
    int N = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N - 1, "K");
    inf.readEoln();

    inf.readEof();
    return 0;
}
