#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 1000, "N");
    inf.readEoln();

    // Read P and T
    int P = inf.readInt(1, N, "P");
    inf.readSpace();
    int T = inf.readInt(1, 10000000, "T");
    inf.readEoln();

    inf.readEof();
}
