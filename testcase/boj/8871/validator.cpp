#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // One natural number n in [1, 1000] on a single line
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    inf.readEof();
}
