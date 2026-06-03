#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int totalDepth = 0;
    for (int i = 0; i < 4; ++i) {
        string kind = inf.readToken("Stair|Es", "kind");
        inf.readSpace();
        int x = inf.readInt(1, 6425, "x");
        inf.readEoln();

        if (kind == "Stair") {
            totalDepth += 17 * x;
        } else {
            totalDepth += 21 * x;
        }
    }

    ensuref(totalDepth <= 6425, "answer exceeds 6425 cm: %d", totalDepth);
    inf.readEof();
}
