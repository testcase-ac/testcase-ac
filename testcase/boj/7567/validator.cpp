#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the bowl‐stack description: must be only '(' or ')', length between 3 and 50.
    inf.readToken("[()]{3,50}", "s");
    inf.readEoln();

    inf.readEof();
    return 0;
}
