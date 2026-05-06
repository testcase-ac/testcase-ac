#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the number of levels N: 1 <= N <= 10
    int N = inf.readInt(1, 10, "N");
    inf.readSpace();

    // Read the counts of red, green, and blue toys: 0 <= count <= 100
    int R = inf.readInt(0, 100, "R");
    inf.readSpace();
    int G = inf.readInt(0, 100, "G");
    inf.readSpace();
    int B = inf.readInt(0, 100, "B");

    // End of the single line
    inf.readEoln();

    // No extra input
    inf.readEof();

    return 0;
}
