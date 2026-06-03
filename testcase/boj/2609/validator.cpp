#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 10000, "a");
    inf.readSpace();
    int b = inf.readInt(1, 10000, "b");
    inf.readEoln();

    inf.readEof();
    return 0;
}
