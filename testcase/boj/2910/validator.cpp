#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int C = inf.readInt(1, 1000000000, "C");
    inf.readEoln();

    inf.readInts(N, 0, C, "message_i");
    inf.readEoln();

    inf.readEof();
}
