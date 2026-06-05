#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000000000000LL, "K");
    inf.readEoln();

    vector<int> v = inf.readInts(n, 1, 1000000000, "v_i");
    inf.readEoln();

    inf.readEof();
}
