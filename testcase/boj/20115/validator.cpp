#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readEoln();

    vector<long long> x = inf.readLongs(n, 1LL, 1000000000LL, "x_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
