#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    ensuref(n % 2 == 1, "n must be odd: %d", n);
    ensuref(m % 2 == 1, "m must be odd: %d", m);

    for (int i = 0; i < n; ++i) {
        string row = inf.readLine("[01]{1,1000}", "row");
        ensuref((int)row.size() == m, "row %d length must be %d, got %d",
                i + 1, m, (int)row.size());
    }

    inf.readEof();
}
