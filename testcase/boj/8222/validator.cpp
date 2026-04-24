#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of elements
    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    // Read each ai
    for (int i = 1; i <= n; i++) {
        // name the parameter with its index for clearer error messages
        char buf[32];
        sprintf(buf, "a_%d", i);
        inf.readInt(1, 1000000, buf);
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
