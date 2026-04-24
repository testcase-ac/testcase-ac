#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, T, C, P with proper whitespace handling
    int N = inf.readInt(2, 90, "N");
    inf.readSpace();
    int T = inf.readInt(1, N - 1, "T");
    inf.readSpace();
    int C = inf.readInt(1, 300, "C");
    inf.readSpace();
    int P = inf.readInt(1, 1000, "P");
    inf.readEoln();

    // No further global constraints to check
    inf.readEof();
    return 0;
}
