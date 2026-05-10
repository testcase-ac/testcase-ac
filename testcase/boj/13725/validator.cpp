#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Constants
    const int MOD = 104857601;
    const int K_MIN = 1, K_MAX = 30000;
    const long long N_MIN = 1, N_MAX = 1000000000000000000LL;
    const int VAL_MIN = 0, VAL_MAX = MOD - 1;

    // Read k and N
    int k = inf.readInt(K_MIN, K_MAX, "k");
    inf.readSpace();
    long long N = inf.readLong(N_MIN, N_MAX, "N");
    inf.readEoln();

    // Read A_1..A_k
    vector<int> A = inf.readInts(k, VAL_MIN, VAL_MAX, "A_i");
    inf.readEoln();

    // Read C_1..C_k
    vector<int> C = inf.readInts(k, VAL_MIN, VAL_MAX, "C_i");
    inf.readEoln();

    inf.readEof();
}
