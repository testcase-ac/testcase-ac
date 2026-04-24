#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read k and p
    int k = inf.readInt(1, N, "k");
    inf.readSpace();
    int p = inf.readInt(1, N, "p");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
