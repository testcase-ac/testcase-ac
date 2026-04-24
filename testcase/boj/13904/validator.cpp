#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of assignments
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // For each assignment, read deadline d and score w
    for (int i = 0; i < N; i++) {
        int d = inf.readInt(1, 1000, "d_i");
        inf.readSpace();
        int w = inf.readInt(1, 100, "w_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
