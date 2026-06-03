#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readSpace();
    int m = inf.readInt(1, 500, "M");
    inf.readSpace();
    int k = inf.readInt(1, 500, "K");
    inf.readEoln();

    ensuref(n % k == 0, "N must be divisible by K: N=%d, K=%d", n, k);
    ensuref(m % k == 0, "M must be divisible by K: M=%d, K=%d", m, k);

    string row_pattern = "[A-Z]{" + to_string(m) + "," + to_string(m) + "}";
    for (int i = 0; i < n; ++i) {
        inf.readToken(row_pattern, "d_i");
        inf.readEoln();
    }

    inf.readEof();
}
