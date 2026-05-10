#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: 1 ≤ N ≤ 100
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // No other data; end of file
    inf.readEof();
    return 0;
}
