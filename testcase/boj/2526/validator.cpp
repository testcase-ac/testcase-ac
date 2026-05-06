#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and P according to problem limits
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int P = inf.readInt(2, 97, "P");
    inf.readEoln();
    inf.readEof();

    return 0;
}
