#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 35, "N");
    inf.readSpace();
    int k = inf.readInt(1, 1000000, "K");
    inf.readSpace();
    int m = inf.readInt(1, 1000000000, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[NY]{1,35}", "adjacency_row");
        ensuref((int)row.size() == n,
                "adjacency row %d has length %d, expected %d",
                i + 1,
                (int)row.size(),
                n);
        ensuref(row[i] == 'N',
                "diagonal entry at row %d, column %d must be N",
                i + 1,
                i + 1);
        inf.readEoln();
    }

    inf.readEof();
}
