#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 500, "R");
    inf.readSpace();
    int c = inf.readInt(1, 500, "C");
    inf.readEoln();

    for (int i = 0; i < r; ++i) {
        string row = inf.readToken("[.#]{1,500}", "board_row");
        inf.readEoln();
        ensuref((int)row.size() == c,
                "row %d length is %d, expected %d",
                i + 1,
                (int)row.size(),
                c);
    }

    inf.readEof();
    return 0;
}
