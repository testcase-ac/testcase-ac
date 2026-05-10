#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer n, 0 <= n < 1000
    int n = inf.readInt(0, 999, "n");
    inf.readEoln();

    inf.readEof();
}
