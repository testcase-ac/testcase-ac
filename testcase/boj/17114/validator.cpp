#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<int> dim(11);
    long long cells = 1;
    for (int i = 0; i < 11; ++i) {
        if (i > 0)
            inf.readSpace();
        dim[i] = inf.readInt(1, 1000000, format("dim_%d", i + 1).c_str());
        cells *= dim[i];
        ensuref(cells <= 1000000,
                "dimension product exceeds 1000000 after dim_%d: %lld",
                i + 1, cells);
    }
    inf.readEoln();

    bool has_tomato = false;
    long long rows = cells / dim[0];
    for (long long row = 0; row < rows; ++row) {
        for (int col = 0; col < dim[0]; ++col) {
            if (col > 0)
                inf.readSpace();
            int value = inf.readInt(-1, 1, "cell");
            if (value != -1)
                has_tomato = true;
        }
        inf.readEoln();
    }

    // CHECK: The statement permits empty cells but defines the instance around stored tomatoes.
    ensuref(has_tomato, "warehouse must contain at least one tomato");

    inf.readEof();
    return 0;
}
