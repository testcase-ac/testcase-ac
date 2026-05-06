#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    // No more input
    inf.readEof();
}
