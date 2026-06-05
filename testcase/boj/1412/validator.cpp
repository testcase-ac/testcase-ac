#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readLine("[YN]{1,50}", "row");
        ensuref((int)row.size() == n, "row %d has length %d, expected %d", i + 1,
                (int)row.size(), n);
        ensuref(row[i] == 'N', "diagonal entry at row %d must be N", i + 1);
    }

    inf.readEof();
}
