#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    inf.readLong(-1000000000LL, 1000000000LL, "k");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, -1000000000LL, 1000000000LL, "a_i");
    inf.readEoln();

    inf.readEof();
}
