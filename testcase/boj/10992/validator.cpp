#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and check its bounds
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // No more content
    inf.readEof();
    return 0;
}
