#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int lineCount = 0;
    long long totalCharacters = 0;
    bool atLineStart = true;

    while (!inf.eof()) {
        char ch = inf.readChar();
        if (ch == '\n') {
            if (atLineStart) {
                ++lineCount;
            }
            atLineStart = true;
            continue;
        }

        if (atLineStart) {
            ++lineCount;
            atLineStart = false;
        }

        unsigned char value = static_cast<unsigned char>(ch);
        ensuref(32 <= value && value <= 127,
                "line %d contains non-ASCII-32-through-127 character with code %d",
                lineCount, static_cast<int>(value));

        ++totalCharacters;
        // CHECK: The statement gives no length bound; cap text input below the
        // local 10,000,000-character string-input limit.
        ensuref(totalCharacters < 10000000LL, "input has too many document characters");
    }

    // CHECK: The statement gives no document-count bound; use the local default
    // cap for an unspecified number of cases.
    ensuref(lineCount <= 100000, "too many document lines: %d", lineCount);
    ensuref(lineCount >= 1, "input must contain at least one document line");
    ensuref(atLineStart, "input must end immediately after the final newline");

    inf.readEof();
}
