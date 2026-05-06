#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read a and b: positive integers ≤ 20000
    int a = inf.readInt(1, 20000, "a");
    inf.readSpace();
    int b = inf.readInt(1, 20000, "b");
    inf.readEoln();
    inf.readEof();
    return 0;
}
