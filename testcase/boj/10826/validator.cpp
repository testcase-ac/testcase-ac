#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: 0 ≤ n ≤ 10000
    int n = inf.readInt(0, 10000, "n");
    inf.readEoln();

    inf.readEof();
    return 0;
}
