#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        for (int j = 1; j <= 4; ++j) {
            string card = inf.readToken("[1-9][mps]", "card");
            if (j < 4) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
