#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    int total = 0;
    for (int group = 1; group <= k; ++group) {
        int c = inf.readInt(0, n, "C_i");
        total += c;
        ensuref(total <= n, "sum of group sizes exceeds N after group %d", group);

        for (int i = 0; i < c; ++i) {
            inf.readSpace();
            inf.readInt(0, n - c, "rank_i");
        }
        inf.readEoln();
    }

    ensuref(total == n, "sum of group sizes must equal N, got %d", total);

    inf.readEof();
    return 0;
}
