#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: the position of the word to query
    inf.readLong(1LL, 1000000LL, "N");
    inf.readEoln();
    inf.readEof();
    return 0;
}
