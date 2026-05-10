#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Read V_1 ... V_N
    vector<long long> V = inf.readLongs(N, 1LL, 1000000000LL, "V_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
