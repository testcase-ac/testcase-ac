#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const string allowed = "1234567890-=WERTYUIOP[]\\SDFGHJKL;'XCVBNM,./ ";
    long long totalChars = 0;
    int lineCount = 0;
    bool hasNonSpace = false;

    while (!inf.eof()) {
        // CHECK: The statement has no length bounds; cap text input to a practical size.
        string line = inf.readLine("[^]{0,10000}", "line");
        ++lineCount;
        totalChars += static_cast<long long>(line.size());
        ensuref(totalChars <= 10000000LL, "total input text is too long");

        for (char ch : line) {
            ensuref(allowed.find(ch) != string::npos, "invalid input character: %c", ch);
            if (ch != ' ') {
                hasNonSpace = true;
            }
        }
    }

    ensuref(lineCount > 0, "input must contain at least one line");
    ensuref(hasNonSpace, "input must contain at least one non-space character");
    inf.readEof();
}
