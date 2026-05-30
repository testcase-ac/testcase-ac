#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    const int MAX_COORD = 1000000000;

    for (int i = 0; i < N; i++) {
        int R = inf.readInt(0, MAX_COORD - 1, "R_i");
        inf.readSpace();
        int S = inf.readInt(0, MAX_COORD - 1, "S_i");
        inf.readEoln();

        ensuref((R & S) == 0, "blocked field at line %d: (%d, %d)", i + 2, R, S);
    }

    inf.readEof();
    return 0;
}
