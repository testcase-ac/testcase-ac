#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 250000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 5000, "K");
    ensuref(K <= N, "K must be <= N, but K=%d and N=%d", K, N);
    inf.readEoln();

    // Read N temperature measurements
    for (int i = 0; i < N; i++) {
        inf.readInt(0, 65535, "temp_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
