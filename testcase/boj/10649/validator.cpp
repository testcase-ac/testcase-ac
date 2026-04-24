#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and H
    int N = inf.readInt(2, 20, "N");
    inf.readSpace();
    long long H = inf.readLong(1LL, 1000000000LL, "H");
    inf.readEoln();

    // Read each cow's parameters: height, weight, strength
    for (int i = 0; i < N; i++) {
        long long h = inf.readLong(1LL, 1000000000LL, "h_i");
        inf.readSpace();
        long long w = inf.readLong(1LL, 1000000000LL, "w_i");
        inf.readSpace();
        long long s = inf.readLong(1LL, 1000000000LL, "s_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
