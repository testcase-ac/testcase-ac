#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000LL, "k");
    inf.readEoln();

    // Read X_i
    vector<long long> x(n);
    for (int i = 0; i < n; ++i) {
        x[i] = inf.readLong(1LL, 1000000000LL, "X_i");
        inf.readEoln();
    }

    inf.readEof();
}
