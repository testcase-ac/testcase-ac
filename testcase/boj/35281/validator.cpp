#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M with proper constraints and canonical integer form.
    int N = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(2, 1000, "M");
    inf.readEoln();

    // No multiple test cases are specified in the statement.

    // Nothing else in the input.
    inf.readEof();
}
