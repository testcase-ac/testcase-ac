#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of piles
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Stones in each pile
    vector<long long> P = inf.readLongs(N, 1LL, 1000000000LL, "P_i");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
