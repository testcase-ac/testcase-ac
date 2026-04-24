#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M, both between 1 and 300 inclusive
    int N = inf.readInt(1, 300, "N");
    inf.readSpace();
    int M = inf.readInt(1, 300, "M");
    inf.readEoln();

    // There should be no more content
    inf.readEof();
    return 0;
}
