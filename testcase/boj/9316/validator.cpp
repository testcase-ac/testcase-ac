#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 200, "N");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
