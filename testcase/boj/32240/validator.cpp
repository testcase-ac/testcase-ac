#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Only one line, one integer N
    long long N = inf.readLong(1LL, 100000000000LL, "N");
    inf.readEoln();

    inf.readEof();
}
