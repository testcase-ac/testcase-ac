#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and validate range
    int N = inf.readInt(1, 8, "N");
    inf.readEoln();

    // No more data
    inf.readEof();
    return 0;
}
