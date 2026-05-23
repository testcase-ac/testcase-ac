#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    for (int i = 0; i < N; i++) {
        inf.readLong(1LL, 2147483647LL, "height");
        inf.readEoln();
    }

    inf.readEof();
}
