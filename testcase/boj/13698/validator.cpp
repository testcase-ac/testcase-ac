#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the mixing sequence: each character must be one of A-F, length 0 to 200.
    // We allow length 0 since "at most 200 mixes" implies zero is possible.
    string moves = inf.readLine("[A-F]{0,200}", "moves");

    // After consuming the line (and its newline), there must be nothing else.
    inf.readEof();
    return 0;
}
