#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

static bool isWordChar(char ch) {
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '-';
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string text;
    while (!inf.eof()) {
        char ch = inf.readChar();
        ensuref(ch == '\n' || (' ' <= ch && ch <= '~'),
                "input contains a non-printable character");
        text.push_back(ch);
        ensuref(text.size() <= 10000, "text length exceeds 10000 characters");
    }

    ensuref(!text.empty(), "input is empty");

    for (size_t start = 0; start < text.size();) {
        size_t end = text.find('\n', start);
        if (end == string::npos) end = text.size();
        if (end > start) {
            ensuref(text[end - 1] != ' ',
                    "text line must not have trailing spaces");
        }
        start = end == text.size() ? end : end + 1;
    }

    bool hasEndMarker = false;
    size_t endMarkerEnd = string::npos;
    for (size_t i = 0; i < text.size();) {
        if (!isWordChar(text[i])) {
            ++i;
            continue;
        }

        size_t start = i;
        while (i < text.size() && isWordChar(text[i])) {
            ++i;
        }

        size_t length = i - start;
        ensuref(length <= 100, "word length exceeds 100");

        string word = text.substr(start, length);
        ensuref(!hasEndMarker, "word appears after E-N-D marker");
        if (word == "E-N-D") {
            hasEndMarker = true;
            endMarkerEnd = i;
        }
    }

    ensuref(hasEndMarker, "missing E-N-D marker");
    ensuref(endMarkerEnd + 1 == text.size() && text[endMarkerEnd] == '\n',
            "E-N-D marker must be followed immediately by the final newline");
    inf.readEof();
}
