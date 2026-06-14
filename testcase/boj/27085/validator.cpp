#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int s = inf.readInt(1, n, "s");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, -1000000000LL, 1000000000LL, "A_i");
    inf.readEoln();

    ensuref(a[s - 1] == 0, "A_s must be 0, found A_%d = %lld", s, a[s - 1]);

    inf.readEof();
}
