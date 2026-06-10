#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 200000, "K");
    inf.readSpace();
    int l = inf.readInt(1, 200000, "L");
    inf.readEoln();

    vector<long long> masses = inf.readLongs(n, 1LL, 1000000000LL, "m_i");
    inf.readEoln();

    vector<int> timings = inf.readInts(k, 1, n, "t_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
