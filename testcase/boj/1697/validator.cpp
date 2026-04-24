#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read Subin's position N and sibling's position K
    inf.readInt(0, 100000, "N");
    inf.readSpace();
    inf.readInt(0, 100000, "K");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
