#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxLineLength = 254;
    const int maxSourceLines = 10000;
    const int maxTotalChars = 1000000;
    int totalChars = 0;

    auto addLineSize = [&](const string& line) {
        totalChars += (int)line.size() + 1;
        ensuref(totalChars <= maxTotalChars,
                "total input size exceeds %d characters", maxTotalChars);
    };

    auto checkCodeLine = [&](const string& line, const char* context, int lineIndex) {
        ensuref((int)line.size() <= maxLineLength,
                "%s line %d is too long: got %d, max is %d",
                context, lineIndex, (int)line.size(), maxLineLength);
        for (int i = 0; i < (int)line.size(); ++i) {
            unsigned char ch = line[i];
            ensuref(32 <= ch && ch <= 126,
                    "%s line %d has invalid character code %d at position %d",
                    context, lineIndex, ch, i + 1);
        }
    };

    int N = inf.readInt(0, 100, "N");
    inf.readEoln();
    addLineSize(to_string(N));

    for (int i = 0; i < N; ++i) {
        string fname = inf.readToken("[!-~]{1,254}", "file_name");
        inf.readEoln();
        addLineSize(fname);

        int lineCnt = 0;
        while (true) {
            string s = inf.readLine("[^]*", "source_line");
            addLineSize(s);
            checkCodeLine(s, "source", lineCnt + 1);
            if (s == "***END***") {
                break;
            }
            ++lineCnt;
            ensuref(lineCnt <= maxSourceLines,
                    "too many lines in source %s: got %d, max is %d",
                    fname.c_str(), lineCnt, maxSourceLines);
        }
    }

    int cmpLines = 0;
    while (true) {
        string s = inf.readLine("[^]*", "compare_source_line");
        addLineSize(s);
        checkCodeLine(s, "comparison source", cmpLines + 1);
        if (s == "***END***") {
            break;
        }
        ++cmpLines;
        ensuref(cmpLines <= maxSourceLines,
                "too many lines in comparison source: got %d, max is %d",
                cmpLines, maxSourceLines);
    }

    inf.readEof();
}
