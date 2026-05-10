#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of records N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Process each record
    for (int i = 0; i < N; i++) {
        // Each line is either the command "ENTER" or a nickname: alphanumeric, length 1..20
        string s = inf.readToken("[A-Za-z0-9]{1,20}", "record");
        inf.readEoln();

        // The first record must be ENTER
        if (i == 0) {
            ensuref(s == "ENTER",
                    "The first record must be ENTER, but found '%s'", s.c_str());
        }
        // No further checks: if s == "ENTER", it's the enter command; otherwise it's a valid nickname
    }

    inf.readEof();
    return 0;
}
