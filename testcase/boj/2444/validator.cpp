#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate N
    int N = inf.readInt(1, 100, "N");
    // After N, there must be exactly one end-of-line
    inf.readEoln();
    // No more characters after the single line
    inf.readEof();

    return 0;
}
