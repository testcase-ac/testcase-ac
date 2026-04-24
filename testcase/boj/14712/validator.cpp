#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 25, "N");
    inf.readSpace();
    int M = inf.readInt(1, 25, "M");
    inf.readEoln();

    // Check the product constraint
    long long prod = 1LL * N * M;
    ensuref(prod <= 25, "Product N*M must be <= 25, but got %d * %d = %lld", N, M, prod);

    inf.readEof();
    return 0;
}
