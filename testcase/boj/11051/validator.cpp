#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K according to problem constraints
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int K = inf.readInt(0, N, "K");
    inf.readEoln();

    inf.readEof();
    return 0;
}
