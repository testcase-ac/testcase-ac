#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    long long m = inf.readLong(1LL, (1LL << 31) - 1, "M");
    inf.readSpace();
    int k = inf.readInt(n, 200000, "K");
    inf.readEoln();

    for (int i = 0; i < k; ++i) {
        int v = inf.readInt(0, 10000, "v_i");
        inf.readSpace();
        long long c = inf.readLong(1LL, (1LL << 31) - 1, "c_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
