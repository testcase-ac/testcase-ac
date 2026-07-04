#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 15, "n");
    inf.readSpace();
    int k = inf.readInt(1, 15, "k");
    inf.readEoln();

    inf.readEof();
    return 0;
}
