#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[OX]{1,1000}", "initial_row");
        ensuref((int)row.size() == m,
                "initial row %d has length %d, expected %d",
                i + 1, (int)row.size(), m);
        inf.readEoln();
    }

    int d = inf.readInt(1, 8, "d");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[OX]{1,1000}", "predicted_row");
        ensuref((int)row.size() == m,
                "predicted row %d has length %d, expected %d",
                i + 1, (int)row.size(), m);
        inf.readEoln();
    }

    inf.readEof();
}
