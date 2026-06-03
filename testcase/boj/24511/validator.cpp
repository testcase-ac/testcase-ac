#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    vector<int> A = inf.readInts(N, 0, 1, "A_i");
    inf.readEoln();

    inf.readLongs(N, 1LL, 1000000000LL, "B_i");
    inf.readEoln();

    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    inf.readLongs(M, 1LL, 1000000000LL, "C_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
