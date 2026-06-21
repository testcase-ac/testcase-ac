#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 20, "r");
    inf.readSpace();
    int c = inf.readInt(1, 20, "c");
    inf.readSpace();
    int k = inf.readInt(0, 1000000, "k");
    inf.readEoln();

    // CHECK: The statement does not require at least one occupied square.
    for (int i = 0; i < r; ++i) {
        string row = inf.readToken("[.#]{1,20}", "row");
        ensuref((int)row.size() == c, "row %d has length %d, expected %d",
                i + 1, (int)row.size(), c);
        inf.readEoln();
    }

    inf.readEof();
}
