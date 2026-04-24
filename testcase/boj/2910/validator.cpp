#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and C
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int C = inf.readInt(1, 1000000000, "C");
    inf.readEoln();

    // Read the sequence of length N, each between 1 and C
    inf.readInts(N, 1, C, "message_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
