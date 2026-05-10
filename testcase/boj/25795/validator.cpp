#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, a, b, c on one line
    int N = inf.readInt(1, 15, "N");
    inf.readSpace();
    int a = inf.readInt(1, 99999, "a");
    inf.readSpace();
    int b = inf.readInt(1, 99999, "b");
    inf.readSpace();
    int c = inf.readInt(1, 99999, "c");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
