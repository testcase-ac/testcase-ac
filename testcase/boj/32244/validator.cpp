#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();
    ensuref(n % 2 == 0, "N must be even, got %d", n);

    for (int i = 0; i < 2 * n; ++i) {
        string name = i < n ? "initial_row" : "target_row";
        string row = inf.readLine("[1-4]{1,1000}", name);
        ensuref((int)row.size() == n, "row %d has length %d, expected %d",
                i + 1, (int)row.size(), n);
    }

    inf.readEof();
}
