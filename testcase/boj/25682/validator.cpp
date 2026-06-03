#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "M");
    inf.readSpace();
    int k = inf.readInt(1, 2000, "K");
    inf.readEoln();

    ensuref(k <= n, "K must not exceed N: K=%d, N=%d", k, n);
    ensuref(k <= m, "K must not exceed M: K=%d, M=%d", k, m);

    string rowPattern = "[BW]{" + to_string(m) + "," + to_string(m) + "}";
    for (int i = 0; i < n; ++i) {
        inf.readLine(rowPattern, "row");
    }

    inf.readEof();
    return 0;
}
