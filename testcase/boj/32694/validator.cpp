#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();
    for (int i = 0; i < Q; i++) {
        long long W = inf.readLong(1LL, 999999999999999999LL, "W");
        inf.readSpace();
        long long B = inf.readLong(1LL, 999999999999999999LL, "B");
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
