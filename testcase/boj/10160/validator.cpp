#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(5, 1000000, "N");
    inf.readSpace();
    int K = inf.readInt(3, 26, "K");
    inf.readEoln();

    inf.readEof();
}
