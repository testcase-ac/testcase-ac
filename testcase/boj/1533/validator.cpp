#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readSpace();
    int s = inf.readInt(1, n, "S");
    inf.readSpace();
    int e = inf.readInt(1, n, "E");
    inf.readSpace();
    inf.readInt(1, 1000000000, "T");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readLine("[0-5]{1,10}", "A_i");
        ensuref((int)row.size() == n, "row %d has length %d, expected %d", i + 1, (int)row.size(), n);
    }

    inf.readEof();
}
