#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int p = inf.readInt(1, n, "P");
    inf.readEoln();

    vector<long long> costs = inf.readLongs(n, 1LL, 1000000000LL, "c_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
