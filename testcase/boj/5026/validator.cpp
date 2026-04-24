#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: N
    string n_line = inf.readLine("[^]*", "N_line");
    // No spaces or tabs allowed
    for (int i = 0; i < (int)n_line.size(); i++) {
        char c = n_line[i];
        ensuref(!isspace(c), "Whitespace not allowed in N line at position %d", i);
        ensuref(isdigit(c), "Non-digit character '%c' in N line at position %d", c, i);
    }
    // Parse N
    long long N = 0;
    for (char c : n_line) {
        N = N * 10 + (c - '0');
        ensuref(N <= 1000, "N = %lld exceeds maximum 1000", N);
    }
    ensuref(N >= 1, "N = %lld is less than minimum 1", N);

    // Read the N problem lines
    for (int idx = 0; idx < N; idx++) {
        string s = inf.readLine("[^]*", "problem_line");
        // Must not be empty
        ensuref(!s.empty(), "Empty problem line at index %d", idx);

        // No whitespace allowed
        for (int i = 0; i < (int)s.size(); i++) {
            char c = s[i];
            ensuref(!isspace(c), "Whitespace not allowed in problem line %d at position %d", idx, i);
        }

        if (s == "P=NP") {
            // OK
        } else {
            // Must be of form a+b
            int plus_cnt = 0;
            int pos = -1;
            for (int i = 0; i < (int)s.size(); i++) {
                if (s[i] == '+') {
                    plus_cnt++;
                    if (pos == -1) pos = i;
                }
            }
            ensuref(plus_cnt == 1,
                    "Problem line %d must contain exactly one '+', found %d", idx, plus_cnt);
            // split
            string a_str = s.substr(0, pos);
            string b_str = s.substr(pos+1);
            ensuref(!a_str.empty(), "Empty left operand in line %d", idx);
            ensuref(!b_str.empty(), "Empty right operand in line %d", idx);
            // digits only
            for (int i = 0; i < (int)a_str.size(); i++) {
                char c = a_str[i];
                ensuref(isdigit(c),
                        "Non-digit character '%c' in left operand at line %d, pos %d", c, idx, i);
            }
            for (int i = 0; i < (int)b_str.size(); i++) {
                char c = b_str[i];
                ensuref(isdigit(c),
                        "Non-digit character '%c' in right operand at line %d, pos %d", c, idx, i);
            }
            // parse values
            long long a_val = 0;
            for (char c : a_str) {
                a_val = a_val * 10 + (c - '0');
                ensuref(a_val <= 1000,
                        "Left operand value %lld exceeds 1000 at line %d", a_val, idx);
            }
            long long b_val = 0;
            for (char c : b_str) {
                b_val = b_val * 10 + (c - '0');
                ensuref(b_val <= 1000,
                        "Right operand value %lld exceeds 1000 at line %d", b_val, idx);
            }
            // Lower bound check
            ensuref(a_val >= 0, "Left operand %lld is negative at line %d", a_val, idx);
            ensuref(b_val >= 0, "Right operand %lld is negative at line %d", b_val, idx);
        }
    }

    inf.readEof();
    return 0;
}
