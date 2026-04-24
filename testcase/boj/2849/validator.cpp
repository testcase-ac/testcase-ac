#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    // Read each modification index
    for (int i = 0; i < Q; i++) {
        inf.readInt(1, N, "pos");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
