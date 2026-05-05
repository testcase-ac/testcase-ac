#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read board size
    int n = inf.readInt(1, 10, "n");
    inf.readEoln();

    // Read the board rows
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Name each cell for clearer error messages
            char name[20];
            sprintf(name, "cell_%d_%d", i + 1, j + 1);
            inf.readInt(0, 1, name);
            if (j < n - 1) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
