#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read the N coordinates
    vector<long long> X = inf.readLongs(N, -1000000000LL, 1000000000LL, "X");
    inf.readEoln();

    inf.readEof();
    return 0;
}
