#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read k and n
    int k = inf.readInt(1, 50, "k");
    inf.readSpace();
    int n = inf.readInt(1, 1000000000, "n");
    inf.readEoln();

    inf.readEof();
}
