#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer N
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // No more input allowed
    inf.readEof();

    return 0;
}
