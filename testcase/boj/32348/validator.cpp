#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 1LL, 1000000000LL, "A_i");
    inf.readEoln();

    vector<long long> b = inf.readLongs(m, 1LL, 1000000000LL, "B_j");
    inf.readEoln();

    inf.readEof();
    return 0;
}
