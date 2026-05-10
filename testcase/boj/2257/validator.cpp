#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

// Compute molecular mass and validate implied properties.
long long computeMassMarker(const string &s) {
    vector<long long> st;          // stack of masses and markers
    const long long MARK = -1;     // marker for '('

    auto massOf = [](char c) -> int {
        if (c == 'H') return 1;
        if (c == 'C') return 12;
        if (c == 'O') return 16;
        return 0;
    };

    int n = (int)s.size();
    for (int i = 0; i < n; ++i) {
        char c = s[i];

        if (c == 'H' || c == 'C' || c == 'O') {
            st.push_back(massOf(c));
        } else if (c == '(') {
            st.push_back(MARK);
        } else if (c == ')') {
            long long group = 0;
            ensuref(!st.empty(),
                    "Unmatched ')' at position %d", i);
            while (!st.empty() && st.back() != MARK) {
                ensuref(st.back() >= 0,
                        "Invalid marker state at position %d", i);
                group += st.back();
                st.pop_back();
            }
            ensuref(!st.empty() && st.back() == MARK,
                    "No matching '(' for ')' at position %d", i);
            st.pop_back(); // remove MARK
            st.push_back(group);
        } else { // digit '2'..'9'
            int mul = c - '0';
            ensuref(!st.empty(),
                    "Digit at position %d has nothing to multiply", i);
            long long last = st.back();
            ensuref(last >= 0,
                    "Digit at position %d cannot multiply '(' directly", i);
            st.pop_back();
            long long prod = last * mul;
            ensuref(prod >= 0 && prod <= 1000000,
                    "Multiplied mass out of range at pos %d: %lld", i, prod);
            st.push_back(prod);
        }
    }

    long long total = 0;
    for (int i = 0; i < (int)st.size(); ++i) {
        ensuref(st[i] != MARK, "Unmatched '(' remaining in stack");
        total += st[i];
        ensuref(total >= 0 && total <= 1000000,
                "Total mass out of range during final sum: %lld", total);
    }
    return total;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single line input: whole formula is one token (no spaces).
    string s = inf.readToken("[^]+", "formula");
    inf.readEoln();

    int n = (int)s.size();
    ensuref(1 <= n && n <= 100,
            "Formula length must be between 1 and 100, got %d", n);

    // Character set and local grammar checks.
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        ensuref(c == 'H' || c == 'C' || c == 'O' ||
                c == '(' || c == ')' ||
                (c >= '2' && c <= '9'),
                "Invalid character '%c' at position %d", c, i);

        if (c >= '2' && c <= '9') {
            ensuref(i > 0,
                    "Digit cannot be at the beginning, at position %d", i);
            char prev = s[i - 1];
            ensuref(prev == ')' || prev == 'H' || prev == 'C' || prev == 'O',
                    "Digit at position %d must follow an atom or ')', previous is '%c'", i, prev);
        }
        if (c == '(') {
            ensuref(i + 1 < n,
                    "'(' at position %d cannot be the last character", i);
        }
        if (c == ')') {
            ensuref(i > 0,
                    "')' at position %d cannot be the first character", i);
        }
    }

    // Parentheses balance.
    int bal = 0;
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        if (c == '(') {
            bal++;
        } else if (c == ')') {
            bal--;
            ensuref(bal >= 0,
                    "More closing than opening parentheses at position %d", i);
        }
    }
    ensuref(bal == 0,
            "Unbalanced parentheses at end of input, balance = %d", bal);

    // First character must be atom or '(' per natural grammar.
    ensuref(s[0] == 'H' || s[0] == 'C' || s[0] == 'O' || s[0] == '(',
            "First character must be 'H','C','O' or '(', got '%c'", s[0]);

    // Global property: molecular mass is guaranteed to be <= 10000,
    // and obviously must be >= 1 (non-empty valid formula).
    long long mass = computeMassMarker(s);
    ensuref(1 <= mass && mass <= 10000,
            "Molecular mass must be between 1 and 10000, got %lld", mass);

    inf.readEof();
}
