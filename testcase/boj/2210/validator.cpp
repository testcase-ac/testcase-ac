#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The input should consist of exactly 5 lines, each with 5 digits [0..9].
    for (int i = 0; i < 5; i++) {
        // Read exactly 5 integers between 0 and 9 on this line
        vector<int> row = inf.readInts(5, 0, 9, "digit");
        // No extra tokens on this line
        inf.readEoln();
    }

    // No extra data after the 5 lines
    inf.readEof();
    return 0;
}
