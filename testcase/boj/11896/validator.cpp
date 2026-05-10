#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read a and b
    int a = inf.readInt(1, 1000000000, "a");
    inf.readSpace();
    int b = inf.readInt(a, 1000000000, "b");
    inf.readEoln();

    inf.readEof();
}
