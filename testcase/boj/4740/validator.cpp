#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement has no line-count bound; this keeps inputs practical.
    const int MAX_LINES = 100000;

    int lineCount = 0;
    while (true) {
        string line = inf.readLine();
        if (line == "***") {
            break;
        }

        ++lineCount;
        ensuref(!line.empty(), "line %d must contain at least one character", lineCount);
        ensuref((int)line.size() <= 80,
                "line %d is too long: %d > 80", lineCount, (int)line.size());
        ensuref(line.front() != ' ' && line.back() != ' ',
                "line %d must not have leading or trailing spaces", lineCount);
        ensuref(line.find("  ") == string::npos,
                "line %d must not contain repeated spaces", lineCount);
        ensuref(lineCount <= MAX_LINES,
                "too many input lines: %d > %d", lineCount, MAX_LINES);

        for (int i = 0; i < (int)line.size(); ++i) {
            unsigned char c = static_cast<unsigned char>(line[i]);
            ensuref(32 <= c && c <= 126,
                    "line %d has non-printable ASCII character at position %d",
                    lineCount, i + 1);
        }
    }

    ensuref(lineCount >= 1, "at least one data line is required");
    inf.readEof();
}
