#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 150, "M");
    inf.readEoln();

    vector<int> degree(n + 1);
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "cow %d has the same pasture twice: %d", i, a);
        ++degree[a];
        ++degree[b];
        ensuref(degree[a] <= 3, "pasture %d is a favorite of more than 3 cows", a);
        ensuref(degree[b] <= 3, "pasture %d is a favorite of more than 3 cows", b);
    }

    inf.readEof();
}
