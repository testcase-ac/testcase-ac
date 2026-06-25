#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "S_i");
    inf.readEoln();

    inf.readEof();
}
