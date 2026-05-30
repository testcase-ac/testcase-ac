#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int test_cases = 0;
    while (true) {
        string s = inf.readToken("(0|[1-9][0-9]{0,5})", "S");
        inf.readEoln();

        int val = 0;
        for (char c : s) {
            val = val * 10 + (c - '0');
        }

        ensuref(val <= 100000, "S (%d) is out of bounds [0,100000]", val);

        if (val == 0) {
            break;
        }

        ++test_cases;
        ensuref(test_cases <= 100000,
                "Number of test cases exceeds 100000");
    }

    inf.readEof();
    return 0;
}
