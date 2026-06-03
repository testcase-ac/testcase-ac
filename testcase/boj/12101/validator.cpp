#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "n");
    inf.readSpace();
    inf.readInt(1, 2147483647, "k");
    inf.readEoln();

    inf.readEof();
    return 0;
}
