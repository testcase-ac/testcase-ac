#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        int ai = inf.readInt(1, 1000000, "a_i");
        sum += ai;
        if (i + 1 < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    ensuref(sum % k == 0, "total pizza weight must be divisible by K: sum=%lld K=%d", sum, k);
    inf.readEof();
}
