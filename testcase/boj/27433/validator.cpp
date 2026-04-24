#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and ensure it's within [0, 20]
    int N = inf.readInt(0, 20, "N");
    inf.readEoln();

    // No more data
    inf.readEof();
    return 0;
}
