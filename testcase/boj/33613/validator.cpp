#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 100000, "N");
    inf.readEoln();

    // Read R and C
    int R = inf.readInt(1, N, "R");
    inf.readSpace();
    int C = inf.readInt(1, N, "C");
    inf.readEoln();

    inf.readEof();
}
