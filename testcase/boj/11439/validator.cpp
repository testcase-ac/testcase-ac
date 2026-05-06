#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, K, M according to problem constraints:
    // 1 ≤ N ≤ 4×10^6, 0 ≤ K ≤ N, 2 ≤ M ≤ 4×10^6
    int N = inf.readInt(1, 4000000, "N");
    inf.readSpace();
    int K = inf.readInt(0, N, "K");
    inf.readSpace();
    int M = inf.readInt(2, 4000000, "M");
    inf.readEoln();

    inf.readEof();
    return 0;
}
