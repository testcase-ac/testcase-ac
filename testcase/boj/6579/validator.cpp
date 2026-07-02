#include "testlib.h"

#include <set>
#include <string>

using namespace std;

class Parser {
public:
    explicit Parser(const string& text) : text_(text) {}

    bool parseExpression() {
        if (!parseTerm()) {
            return false;
        }
        while (peek('+') || peek('-')) {
            ++pos_;
            if (!parseTerm()) {
                return false;
            }
        }
        return pos_ == text_.size();
    }

private:
    bool parseTerm() {
        if (!parseFactor()) {
            return false;
        }
        while (peek('*')) {
            ++pos_;
            if (!parseFactor()) {
                return false;
            }
        }
        return true;
    }

    bool parseFactor() {
        if (peek('{')) {
            return parseSet();
        }
        if (peek('(')) {
            ++pos_;
            if (!parseInnerExpression()) {
                return false;
            }
            if (!peek(')')) {
                return false;
            }
            ++pos_;
            return true;
        }
        return false;
    }

    bool parseInnerExpression() {
        if (!parseTerm()) {
            return false;
        }
        while (peek('+') || peek('-')) {
            ++pos_;
            if (!parseTerm()) {
                return false;
            }
        }
        return true;
    }

    bool parseSet() {
        ++pos_;
        set<char> seen;
        while (pos_ < text_.size() && isElement(text_[pos_])) {
            // CHECK: The statement defines set literals, so duplicate elements
            // inside one literal are rejected even though the character grammar
            // alone would allow repeated capital letters.
            if (!seen.insert(text_[pos_]).second) {
                return false;
            }
            ++pos_;
        }
        if (!peek('}')) {
            return false;
        }
        ++pos_;
        return true;
    }

    bool peek(char c) const {
        return pos_ < text_.size() && text_[pos_] == c;
    }

    static bool isElement(char c) {
        return 'A' <= c && c <= 'Z';
    }

    const string& text_;
    size_t pos_ = 0;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int lineCount = 0;
    while (!inf.seekEof()) {
        string line = inf.readLine("[^]{1,255}", "expression");
        ++lineCount;
        for (int i = 0; i < (int)line.size(); ++i) {
            char c = line[i];
            ensuref(('A' <= c && c <= 'Z') || c == '{' || c == '}' || c == '+' ||
                        c == '-' || c == '*' || c == '(' || c == ')',
                    "invalid character '%c' on line %d, position %d", c, lineCount, i + 1);
        }
        ensuref(Parser(line).parseExpression(), "invalid expression syntax on line %d", lineCount);
    }

    ensuref(lineCount >= 1, "input must contain at least one expression");
    inf.readEof();
}
