#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 200000;
    const int maxM = 200000;
    const long long maxA = 1000000000LL;

    int n = inf.readInt(1, maxN, "n");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 1LL, maxA, "a_i");
    inf.readEoln();

    int m = inf.readInt(1, maxM, "m");
    inf.readEoln();

    for (int query = 1; query <= m; ++query) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        int i = inf.readInt(1, n, "i");
        inf.readSpace();

        if (type == 1) {
            long long value = inf.readLong(1LL, maxA, "j");
            a[i - 1] = value;
        } else {
            inf.readLong(1LL, a[i - 1], "j");
        }
        inf.readEoln();
    }

    inf.readEof();
}
