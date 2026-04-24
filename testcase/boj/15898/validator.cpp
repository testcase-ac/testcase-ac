#include "testlib.h"
#include <cstdio>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of ingredients
    int n = inf.readInt(3, 10, "n");
    inf.readEoln();

    // For each ingredient
    for (int i = 0; i < n; i++) {
        // Read the 4x4 efficacy grid
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                char name[50];
                std::sprintf(name, "x[%d][%d][%d]", i, r, c);
                inf.readInt(-9, 9, name);
                if (c < 3) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }
        // Read the 4x4 element color grid
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                char name[50];
                std::sprintf(name, "col[%d][%d][%d]", i, r, c);
                inf.readToken("[RBGYW]", name);
                if (c < 3) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }
    }

    inf.readEof();
    return 0;
}
