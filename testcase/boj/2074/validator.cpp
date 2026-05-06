#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer P, 1 ≤ P ≤ 20000
    int P = inf.readInt(1, 20000, "P");
    inf.readEoln();

    inf.readEof();
}
