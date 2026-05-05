#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 10, "N");
    inf.readEoln();

    // Read P0..P{N-1}
    vector<int> P = inf.readInts(N, 1, 50, "P");
    inf.readEoln();

    // Read M
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Global constraint: must be able to buy at least one digit
    int minP = *min_element(P.begin(), P.end());
    ensuref(minP <= M,
            "No purchasable digit: minimum price %d exceeds M = %d", minP, M);

    inf.readEof();
    return 0;
}
