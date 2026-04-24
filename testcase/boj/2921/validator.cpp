#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: the size of the domino set
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
