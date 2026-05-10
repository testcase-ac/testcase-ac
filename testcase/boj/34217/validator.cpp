#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: A B
    int A = inf.readInt(1, 1000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 1000, "B");
    inf.readEoln();

    // Second line: C D
    int C = inf.readInt(1, 30, "C");
    inf.readSpace();
    int D = inf.readInt(1, 30, "D");
    inf.readEoln();

    inf.readEof();
}
