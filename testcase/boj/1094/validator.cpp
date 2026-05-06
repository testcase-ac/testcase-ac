#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // X: desired length, natural number between 1 and 64 inclusive
    int X = inf.readInt(1, 64, "X");
    inf.readEoln();
    inf.readEof();
    return 0;
}
