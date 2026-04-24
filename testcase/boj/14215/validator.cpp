#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read three positive integers a, b, c in [1, 100].
    int a = inf.readInt(1, 100, "a");
    inf.readSpace();
    int b = inf.readInt(1, 100, "b");
    inf.readSpace();
    int c = inf.readInt(1, 100, "c");
    inf.readEoln();

    // No further global constraints beyond ranges.
    inf.readEof();
    return 0;
}
