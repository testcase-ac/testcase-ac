#include "testlib.h"

#include <string>

using namespace std;

namespace {

constexpr int kMaxNonSpaceLength = 15000;

string s;
int pos = 0;
int nonSpaceLength = 0;

bool isDigit(char c) {
    return '0' <= c && c <= '9';
}

bool isAlpha(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

void requireAtEnd(bool condition, const char* message) {
    ensuref(condition, "%s at position %d", message, pos);
}

void readPositiveInteger() {
    int start = pos;
    while (pos < int(s.size()) && isDigit(s[pos])) {
        ++pos;
    }

    int len = pos - start;
    ensuref(1 <= len && len <= 17,
            "integer length must be 1..17 at position %d, got %d", start, len);
    ensuref(s[start] != '0', "integer has leading zero at position %d", start);
}

void readString() {
    int start = pos;
    while (pos < int(s.size()) && isAlpha(s[pos])) {
        ++pos;
    }
    ensuref(pos > start, "string must contain at least one letter at position %d", start);
}

void readObject();

void readElement() {
    requireAtEnd(pos < int(s.size()), "expected element");

    if (s[pos] == '[') {
        readObject();
    } else if (isDigit(s[pos])) {
        readPositiveInteger();
    } else if (isAlpha(s[pos])) {
        readString();
    } else {
        ensuref(false, "invalid element start '%c' at position %d", s[pos], pos);
    }
}

void readRequiredSpace(const char* context) {
    ensuref(pos < int(s.size()) && s[pos] == ' ', "expected one space %s at position %d",
            context, pos);
    ++pos;
}

void readObject() {
    ensuref(pos < int(s.size()) && s[pos] == '[', "expected '[' at position %d", pos);
    ++pos;
    readRequiredSpace("after '['");

    if (pos < int(s.size()) && s[pos] == ']') {
        ++pos;
        return;
    }

    while (true) {
        readElement();
        readRequiredSpace("after element");
        requireAtEnd(pos < int(s.size()), "expected ']' or another element");

        if (s[pos] == ']') {
            ++pos;
            return;
        }
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    s = inf.readLine("[^]{1,30000}", "ason");

    for (int i = 0; i < int(s.size()); ++i) {
        ensuref(s[i] == '[' || s[i] == ']' || s[i] == ' ' || isDigit(s[i]) || isAlpha(s[i]),
                "invalid character at position %d", i);
        if (s[i] != ' ') {
            ++nonSpaceLength;
        }
    }
    ensuref(nonSpaceLength <= kMaxNonSpaceLength,
            "length excluding spaces must be at most %d, got %d", kMaxNonSpaceLength,
            nonSpaceLength);

    readObject();
    ensuref(pos == int(s.size()), "extra characters after root object at position %d", pos);
    inf.readEof();
}
