#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(2, 1500, "R");
    inf.readSpace();
    int c = inf.readInt(2, 1500, "C");
    inf.readEoln();

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            string cell = inf.readToken("[AB][1-9][0-9]?", "cell");
            int trees = stoi(cell.substr(1));
            ensuref(1 <= trees && trees <= 99,
                    "tree count at row %d column %d is %d, expected 1..99",
                    i + 1, j + 1, trees);

            if (j + 1 == c) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
