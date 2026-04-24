#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int case_cnt = 0;
    // Read until EOF: each test case has two tokens and one EOL
    while (!inf.eof()) {
        // Read first fruit name: 1 to 100 letters (uppercase or lowercase)
        string s1 = inf.readToken("[A-Za-z]{1,100}", "fruit1");
        inf.readSpace();                     // exactly one whitespace between names
        // Read second fruit name
        string s2 = inf.readToken("[A-Za-z]{1,100}", "fruit2");
        inf.readEoln();                     // end of this test case line

        case_cnt++;
        ensuref(case_cnt <= 100000,
                "Number of test cases exceeds limit: %d > 100000", case_cnt);
    }

    inf.readEof(); // no extra characters after the last newline
    return 0;
}
