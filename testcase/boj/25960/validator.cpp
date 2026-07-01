#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    int kingCount = 0;
    int pawnCount = 0;
    int queenCount = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            string cell = inf.readToken("0|Q|R|B|N|K|P", "cell");
            if (cell == "K") {
                ++kingCount;
            } else if (cell == "P") {
                ++pawnCount;
            } else if (cell == "Q") {
                ++queenCount;
            }

            if (j + 1 == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    ensuref(kingCount == 1, "expected exactly one K, found %d", kingCount);
    ensuref(pawnCount == 1, "expected exactly one P, found %d", pawnCount);
    ensuref(queenCount <= 1, "expected at most one Q, found %d", queenCount);

    inf.readEof();
}
