#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N on the first line
    int N = inf.readInt(1, 2000, "N");
    inf.readEoln();

    // Read exactly N integers on the second line, separated by single spaces
    for (int i = 0; i < N; ++i) {
        inf.readLong(-1000000000LL, 1000000000LL, "A_i");
        if (i + 1 < N) inf.readSpace();
    }
    inf.readEoln();

    inf.readEof();
    return 0;
}
