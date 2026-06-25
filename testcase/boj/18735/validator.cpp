#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<long long> c = inf.readLongs(n, 1LL, 1000000000LL, "c_i");
    (void)c;
    inf.readEoln();

    inf.readEof();
}
