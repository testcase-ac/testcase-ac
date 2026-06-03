#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 5, "N");
    ensuref(n % 2 == 1, "N must be odd, but found %d", n);
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }

            if ((i + j) % 2 == 0) {
                inf.readInt(0, 5, "cell");
            } else {
                inf.readToken("[+\\-*]", "op");
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}
