#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the input number n
    int n = inf.readInt(3, 3000, "n");
    // Ensure n is a multiple of 3
    ensuref(n % 3 == 0, "n (%d) is not a multiple of 3", n);
    // The line must end here
    inf.readEoln();
    // No extra data allowed
    inf.readEof();

    return 0;
}
