#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_LINES = 100000;
    const int MAX_LINE_LENGTH = 1000000;
    const int MAX_TOTAL_LENGTH = 10000000;

    int lineCount = 0;
    int lineLength = 0;
    int totalLength = 0;
    bool sawAnyLine = false;
    bool lastWasNewline = false;

    while (!inf.eof()) {
        char ch = inf.readChar();

        if (ch == '\n') {
            ensuref(lineLength > 0, "line %d is empty", lineCount + 1);
            ++lineCount;
            ensuref(lineCount <= MAX_LINES,
                    "number of message lines exceeds %d", MAX_LINES);
            sawAnyLine = true;
            lineLength = 0;
            lastWasNewline = true;
            continue;
        }

        ensuref(ch == '.' || ch == '-',
                "line %d contains invalid character with code %d",
                lineCount + 1, int(static_cast<unsigned char>(ch)));

        ++lineLength;
        ++totalLength;
        // CHECK: The statement gives no length bound, so cap unbounded string input.
        ensuref(lineLength <= MAX_LINE_LENGTH,
                "line %d length exceeds %d", lineCount + 1, MAX_LINE_LENGTH);
        ensuref(totalLength <= MAX_TOTAL_LENGTH,
                "total message length exceeds %d", MAX_TOTAL_LENGTH);
        lastWasNewline = false;
    }

    ensuref(sawAnyLine, "input must contain at least one message line");
    ensuref(lastWasNewline, "input must end with a newline");

    inf.readEof();
}
