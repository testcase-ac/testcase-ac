#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T
    int T = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Read M and type
        int M = inf.readInt(1, 500, "M");
        inf.readSpace();
        string type = inf.readToken("[CN]", "type");
        inf.readEoln();

        // Read the second line: M tokens separated by single spaces, then EOL
        if (type == "C") {
            // Expect M uppercase letters
            for (int i = 0; i < M; i++) {
                if (i > 0) inf.readSpace();
                inf.readToken("[A-Z]", "letter");
            }
            inf.readEoln();
        } else {
            // type == "N": Expect M integers 1..26
            for (int i = 0; i < M; i++) {
                if (i > 0) inf.readSpace();
                inf.readInt(1, 26, "number");
            }
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
