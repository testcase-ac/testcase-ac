#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();
    inf.readEof();

    return 0;
}
