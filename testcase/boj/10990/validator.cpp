#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and check the range
    int N = inf.readInt(1, 100, "N");
    // After N there must be exactly one newline
    inf.readEoln();

    // No extra content allowed
    inf.readEof();

    return 0;
}
