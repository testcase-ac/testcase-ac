#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    long long m = inf.readLong(1LL, 2147483647LL, "M");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 1LL, 2147483647LL, "a_i");
    inf.readEoln();

    inf.readEof();
}
