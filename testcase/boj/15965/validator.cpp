#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K
    int K = inf.readInt(1, 500000, "K");
    inf.readEoln();

    // No extra lines allowed
    inf.readEof();
}
