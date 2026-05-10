#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    long long n = inf.readLong(1LL, 1000000000000000LL, "n");
    inf.readSpace();
    int k = inf.readInt(2, 1000, "k");
    inf.readEoln();

    inf.readEof();
}
