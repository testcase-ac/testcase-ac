#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of trees
    int N = inf.readInt(2, 200000, "N");
    inf.readEoln();

    // Read N coordinates, one per line
    for (int i = 1; i <= N; i++) {
        inf.readInt(0, 199999, "X");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
