#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

string s;
int n;
int pos;
vector<bool> seen;

void parse_expr();

void parse_factor() {
    // factor -> LETTER | '(' expr ')'
    ensuref(pos < n, "Expected operand or '(', but got end of line at position %d", pos);
    char c = s[pos];
    if (c == '(') {
        pos++;
        parse_expr();
        ensuref(pos < n && s[pos] == ')',
                "Expected ')' to match '(' at position %d, but found '%c' at position %d",
                pos-1, pos < n ? s[pos] : ' ', pos);
        pos++;
    } else if (c >= 'A' && c <= 'Z') {
        int idx = c - 'A';
        ensuref(!seen[idx],
                "Duplicate operand letter '%c' at position %d", c, pos);
        seen[idx] = true;
        pos++;
    } else {
        ensuref(false,
                "Invalid character '%c' at position %d: expected uppercase letter or '('", c, pos);
    }
}

void parse_term() {
    // term -> factor { ('*'|'/') factor }
    parse_factor();
    while (pos < n && (s[pos] == '*' || s[pos] == '/')) {
        pos++;
        parse_factor();
    }
}

void parse_expr() {
    // expr -> term { ('+'|'-') term }
    parse_term();
    while (pos < n && (s[pos] == '+' || s[pos] == '-')) {
        pos++;
        parse_term();
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the expression: only uppercase letters and + - * / ( )
    // length 1..100
    s = inf.readLine("[A-Z+\\-*/()]{1,100}", "expression");
    n = (int)s.size();
    // Prepare for parsing
    pos = 0;
    seen.assign(26, false);

    // Parse under grammar:
    // expr -> term {(+|-) term}
    // term -> factor {(*|/) factor}
    // factor -> LETTER | '(' expr ')'
    parse_expr();
    // Entire string must be consumed
    ensuref(pos == n, "Extra or missing tokens: parsed up to position %d of %d", pos, n);

    inf.readEof();
    return 0;
}
