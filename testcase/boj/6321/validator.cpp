#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of computers
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Read each computer name
    for (int i = 0; i < n; i++) {
        // Name must be 1 to 50 uppercase letters, no spaces
        inf.readToken("[A-Z]{1,50}", "computer_name");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
