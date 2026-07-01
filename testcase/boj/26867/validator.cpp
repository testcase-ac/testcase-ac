#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string row = inf.readToken("[.#?]{1,1000}", "s_i");
        ensuref(static_cast<int>(row.size()) == n,
                "row %d has length %d, expected %d", i,
                static_cast<int>(row.size()), n);
        inf.readEoln();
    }

    inf.readEof();
}
