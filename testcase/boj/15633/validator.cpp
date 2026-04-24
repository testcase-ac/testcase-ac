#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: a natural number between 1 and 10000 inclusive
    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
