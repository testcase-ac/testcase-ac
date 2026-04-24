#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: purchased amounts A, B, C
    int A = inf.readInt(1, 500, "A");
    inf.readSpace();
    int B = inf.readInt(1, 500, "B");
    inf.readSpace();
    int C = inf.readInt(1, 500, "C");
    inf.readEoln();

    // Second line: required ratios I, J, K
    int I = inf.readInt(1, 50, "I");
    inf.readSpace();
    int J = inf.readInt(1, 50, "J");
    inf.readSpace();
    int K = inf.readInt(1, 50, "K");
    inf.readEoln();

    // No extra content
    inf.readEof();
    return 0;
}
