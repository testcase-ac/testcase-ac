#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n, k, x
    int n = inf.readInt(1, 80, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readSpace();
    int x = inf.readInt(1, 200, "x");
    inf.readEoln();

    // Read n lines of (a, b)
    vector<pair<int, int>> ab(n);
    for (int i = 0; i < n; ++i) {
        int a = inf.readInt(0, x, "a_i");
        inf.readSpace();
        int b = inf.readInt(0, x, "b_i");
        inf.readEoln();

        ensuref(a + b == x, "For person %d, a_i + b_i = %d + %d = %d != x = %d", i+1, a, b, a+b, x);
        ab[i] = {a, b};
    }

    inf.readEof();
}
