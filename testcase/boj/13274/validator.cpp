#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 1000, "K");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, -1000000000000000000LL, 1000000000000000000LL, "A_i");
    inf.readEoln();

    for (int i = 0; i < k; ++i) {
        int l = inf.readInt(1, n, "L");
        inf.readSpace();
        int r = inf.readInt(l, n, "R");
        inf.readSpace();
        inf.readInt(-1000000000, 1000000000, "X");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
