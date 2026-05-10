#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N (degree of polynomial)
    int N = inf.readInt(0, 250000, "N");
    inf.readEoln();

    // 2. Read coefficients a_0 ... a_N
    vector<int> a = inf.readInts(N + 1, 0, 786432, "a_i");
    inf.readEoln();

    // 3. Read K (number of queries)
    int K = inf.readInt(1, 250000, "K");
    inf.readEoln();

    // 4. Read x_1 ... x_K
    vector<int> x = inf.readInts(K, 0, 786432, "x_j");
    inf.readEoln();

    inf.readEof();
}
