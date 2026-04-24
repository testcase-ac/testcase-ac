#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single input: the first number N
    int N = inf.readInt(1, 30000, "N");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
