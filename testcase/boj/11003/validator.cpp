#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N and L
    int N = inf.readInt(1, 5000000, "N");
    inf.readSpace();
    int L = inf.readInt(1, N, "L");
    inf.readEoln();

    // Second line: N values A_i
    vector<long long> A = inf.readLongs(N, -1000000000LL, 1000000000LL, "A_i");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
