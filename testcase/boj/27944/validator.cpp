#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000000LL, "A_i");
    inf.readEoln();

    inf.readEof();
}
