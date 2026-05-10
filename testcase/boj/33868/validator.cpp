#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of AC submissions
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Each submission: time T and code length B
    for (int i = 0; i < N; i++) {
        inf.readInt(1, 1500, "T_i");
        inf.readSpace();
        inf.readInt(50, 5000, "B_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
