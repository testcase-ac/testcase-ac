#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of problems N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read the times T_i
    vector<long long> T = inf.readLongs(N, 1LL, 1000000000LL, "T_i");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
