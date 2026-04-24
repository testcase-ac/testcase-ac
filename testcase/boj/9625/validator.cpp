#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K: number of button presses
    int K = inf.readInt(1, 45, "K");
    inf.readEoln();

    // No more input allowed
    inf.readEof();
    return 0;
}
