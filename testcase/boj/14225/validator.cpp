#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: size of sequence S
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    // Read N natural numbers, each in [1, 100000]
    vector<long long> S = inf.readLongs(N, 1LL, 100000LL, "S_i");
    inf.readEoln();

    // No further global properties are specified in the statement,
    // so we do not check subset-sum properties here.

    inf.readEof();
}
