#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(4, 1000, "N");
    inf.readEoln();

    // Read K
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // No extra data
    inf.readEof();

    return 0;
}
