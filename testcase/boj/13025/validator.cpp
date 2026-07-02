#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long l = inf.readLong(1LL, 1000000000000LL, "l");
    inf.readSpace();
    long long r = inf.readLong(l, 1000000000000LL, "r");
    inf.readSpace();
    long long maxK = min(1000000LL, r - l + 1);
    inf.readLong(1LL, maxK, "k");
    inf.readEoln();

    inf.readEof();
}
