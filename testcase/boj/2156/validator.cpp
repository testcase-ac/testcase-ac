#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of wine glasses
    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    // Amount in each glass
    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 1000, "a_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
