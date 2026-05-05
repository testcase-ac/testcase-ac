#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: 9 <= N <= 1,000,000
    int N = inf.readInt(9, 1000000, "N");
    inf.readEoln();

    inf.readEof();
    return 0;
}
