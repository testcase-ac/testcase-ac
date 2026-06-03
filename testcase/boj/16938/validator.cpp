#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 15, "N");
    inf.readSpace();
    long long l = inf.readLong(1LL, 1000000000LL, "L");
    inf.readSpace();
    long long r = inf.readLong(l, 1000000000LL, "R");
    inf.readSpace();
    int x = inf.readInt(1, 1000000, "X");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 1000000, "A_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
