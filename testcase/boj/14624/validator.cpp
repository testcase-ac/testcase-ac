#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate N
    int N = inf.readInt(3, 50, "N");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
