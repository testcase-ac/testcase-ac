#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read the N heights
    vector<long long> H = inf.readLongs(N, 1LL, 1000000000LL, "H_i");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
