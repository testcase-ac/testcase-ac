#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Problem has no input, so we must be immediately at EOF
    inf.readEof();
    return 0;
}
