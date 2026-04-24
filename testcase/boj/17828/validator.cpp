#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and X
    int N = inf.readInt(1, 5000000, "N");
    inf.readSpace();
    int X = inf.readInt(1, 500000000, "X");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
