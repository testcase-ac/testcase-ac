#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There should be exactly 10 lines, each with one integer 0 <= x <= 1000
    for (int i = 1; i <= 10; i++) {
        // Read one integer in [0,1000]
        string name = string("a_") + to_string(i);
        inf.readInt(0, 1000, name.c_str());
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
