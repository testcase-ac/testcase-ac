#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and C
    int N = inf.readInt(1, 30, "N");
    inf.readSpace();
    long long C = inf.readLong(0LL, 1000000000LL, "C");
    inf.readEoln();

    // Read weights
    vector<long long> w = inf.readLongs(N, 1LL, 1000000000LL, "w_i");
    inf.readEoln();

    inf.readEof();
}
