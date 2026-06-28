#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    vector<long long> s = inf.readLongs(n, 1LL, 1000000000LL, "s_i");
    (void)s;
    inf.readEoln();

    inf.readEof();
}
