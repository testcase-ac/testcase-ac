#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M with specified bounds
    int N = inf.readInt(1, 2016, "N");
    inf.readSpace();
    int M = inf.readInt(1, 2016, "M");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
