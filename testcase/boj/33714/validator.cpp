#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    inf.readLong(0LL, 1000000000LL, "K");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 0LL, 1000000000LL, "A_i");
    (void)a;
    inf.readEoln();

    inf.readEof();
    return 0;
}
