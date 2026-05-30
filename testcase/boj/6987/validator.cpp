#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int LINES = 4;
    const int TEAMS = 6;
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < TEAMS; j++) {
            char bufW[20];
            sprintf(bufW, "w_%d_%d", i+1, j+1);
            inf.readInt(0, 6, bufW);
            inf.readSpace();

            char bufD[20];
            sprintf(bufD, "d_%d_%d", i+1, j+1);
            inf.readInt(0, 6, bufD);
            inf.readSpace();

            char bufL[20];
            sprintf(bufL, "l_%d_%d", i+1, j+1);
            inf.readInt(0, 6, bufL);

            if (j < TEAMS - 1) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
    return 0;
}
