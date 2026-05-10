#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_CASES = 100000;
    int case_cnt = 0;

    while (true) {
        string s = inf.readToken("[A-Z\\.]{3,9}|end", "board or end");
        // Accept only "end" or a board of exactly 9 chars
        if (s == "end") {
            inf.readEoln();
            break;
        }
        ++case_cnt;
        ensuref(case_cnt <= MAX_CASES, "Too many test cases: %d (max %d)", case_cnt, MAX_CASES);
        ensuref(s.length() == 9, "Each board line must have exactly 9 characters, got %d", (int)s.length());
        for (int i = 0; i < 9; ++i) {
            ensuref(s[i] == 'X' || s[i] == 'O' || s[i] == '.', "Invalid character at position %d: '%c'", i, s[i]);
        }
        inf.readEoln();
    }

    inf.readEof();
}
