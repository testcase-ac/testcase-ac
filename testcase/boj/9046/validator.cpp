#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 20, "T");
    inf.readEoln();

    // Each test case: one line of length [1,255], containing only lowercase letters and spaces
    for (int tc = 0; tc < T; tc++) {
        // Regex: [a-z\ ] matches lowercase letters or space; {1,255} enforces length
        string s = inf.readLine("[a-z\\ ]{1,255}", "s");
        ensuref(s.front() != ' ' && s.back() != ' ',
                "sentence %d must not have leading or trailing spaces", tc + 1);
        ensuref(s.find("  ") == string::npos,
                "sentence %d must not contain repeated spaces", tc + 1);
    }

    inf.readEof();
    return 0;
}
