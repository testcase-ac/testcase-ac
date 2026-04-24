#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There must be exactly 36 moves
    for (int i = 0; i < 36; i++) {
        // Each move is exactly a column A-F and a row 1-6
        inf.readToken("[A-F][1-6]", "square");
        inf.readEoln();
    }

    // No extra input
    inf.readEof();
    return 0;
}
