#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the variable name: only English letters and underscores, length 1 to 100
    inf.readToken("[A-Za-z_]{1,100}", "variable");
    inf.readEoln();
    inf.readEof();

    return 0;
}
