#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int lines = 0;
    while (true) {
        string s = inf.readLine("[^]{1,79}", "s");
        if (s == "#") {
            break;
        }

        ++lines;
        // CHECK: the statement does not cap the number of input strings.
        ensuref(lines <= 100000, "too many input strings: %d", lines);
        ensuref(s.find('#') == string::npos, "input string contains #");
        ensuref(s.front() != ' ', "input string has a leading space");
        ensuref(s.back() != ' ', "input string has a trailing space");
        ensuref(s.find("  ") == string::npos, "input string has consecutive spaces");
    }

    ensuref(lines >= 1, "at least one input string is required");
    inf.readEof();
}
