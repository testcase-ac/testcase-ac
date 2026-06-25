#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    int countO = 0;
    int countX = 0;
    for (int i = 0; i < 2 * n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        std::string card = inf.readToken("O|X", "card");
        if (card == "O") {
            ++countO;
        } else {
            ++countX;
        }
    }
    inf.readEoln();

    ensuref(countO == n, "expected %d O cards, found %d", n, countO);
    ensuref(countX == n, "expected %d X cards, found %d", n, countX);

    inf.readEof();
}
