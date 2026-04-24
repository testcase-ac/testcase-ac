#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 200, "N");
    inf.readSpace();
    int M = inf.readInt(1, 20, "M");
    inf.readEoln();

    // Read M chapters: days and pages
    for (int i = 0; i < M; i++) {
        int d = inf.readInt(1, 20, "d_i");
        inf.readSpace();
        int p = inf.readInt(1, 300, "p_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
