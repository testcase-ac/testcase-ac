#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, K, P
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int K = inf.readInt(1, 50, "K");
    inf.readSpace();
    int P = inf.readInt(1, K, "P");
    inf.readEoln();

    // Total breads should be N * K
    long long total = 1LL * N * K;
    // Read the cream indicators: 0 or 1
    vector<int> a = inf.readInts((int)total, 0, 1, "a_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
