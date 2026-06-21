#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 2000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n - 1, 0, 10000, "A_i");
    (void)a;
    inf.readEoln();

    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int from = inf.readInt(0, n - 1, "a_i");
        inf.readSpace();
        int to = inf.readInt(0, n - 1, "b_i");
        inf.readEoln();

        ensuref(from != to, "query %d has equal endpoints: %d", i, from);
    }

    inf.readEof();
}
