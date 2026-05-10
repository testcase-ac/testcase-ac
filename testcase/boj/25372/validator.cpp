#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        // Read the string: must be 1~20 chars, only [0-9A-Za-z]
        string s = inf.readToken("[0-9A-Za-z]{1,20}", "password");
        inf.readEoln();
        // No further checks needed: length and charset are validated above
    }

    inf.readEof();
}
