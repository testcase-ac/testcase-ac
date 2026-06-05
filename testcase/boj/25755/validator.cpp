#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[LRUD]", "W");
    inf.readSpace();
    int n = inf.readInt(2, 20, "N");
    inf.readEoln();

    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            inf.readInt(1, 9, "a_ij");
            if (col + 1 == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
