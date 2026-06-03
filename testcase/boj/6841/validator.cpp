#include "testlib.h"

#include <cctype>
#include <string>

using namespace std;

namespace {
const int MAX_LINES = 100000;
const int MAX_LINE_LENGTH = 100000;
const int MAX_TOTAL_CHARS = 5000000;

bool isAllowedChar(unsigned char c) {
    return ('A' <= c && c <= 'Z') || (isprint(c) && ispunct(c) && c != '"' && c != '\'');
}
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int lines = 0;
    int totalChars = 0;
    bool seenTerminator = false;

    while (!inf.seekEof()) {
        // CHECK: The statement gives no input-size bounds; these caps keep open-ended interactive input finite.
        ensuref(lines < MAX_LINES, "too many input lines");

        string s = inf.readLine("[^]{1,100000}", "text");
        ++lines;
        totalChars += (int)s.size();

        ensuref((int)s.size() <= MAX_LINE_LENGTH, "line %d is too long", lines);
        ensuref(totalChars <= MAX_TOTAL_CHARS, "input has too many characters");

        for (int i = 0; i < (int)s.size(); ++i) {
            unsigned char c = (unsigned char)s[i];
            ensuref(isAllowedChar(c), "invalid character on line %d at column %d", lines, i + 1);
        }

        if (seenTerminator) {
            ensuref(false, "input continues after TTYL");
        }
        if (s == "TTYL") {
            seenTerminator = true;
        }
    }

    ensuref(lines > 0, "input must contain at least one line");
    ensuref(seenTerminator, "input must end with TTYL");
    inf.readEof();
}
