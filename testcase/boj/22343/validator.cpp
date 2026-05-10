#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

// Checks if s is a valid parenthesis string (올바른 괄호열)
void validate_parenthesis(const string& s, const char* name) {
    int bal = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        ensuref(c == '(' || c == ')', "%s contains invalid character at position %zu: '%c'", name, i+1, c);
        if (c == '(') ++bal;
        else --bal;
        ensuref(bal >= 0, "%s is not a valid parenthesis string: too many closing at position %zu", name, i+1);
    }
    ensuref(bal == 0, "%s is not a valid parenthesis string: unbalanced, final balance = %d", name, bal);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    long long total_A = 0, total_B = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        string A = inf.readLine("[()]{1,3000000}", "A");
        ensuref(!A.empty(), "A in test case %d is empty", tc);
        validate_parenthesis(A, "A");
        total_A += A.size();

        string B = inf.readLine("[()]{1,3000000}", "B");
        ensuref(!B.empty(), "B in test case %d is empty", tc);
        validate_parenthesis(B, "B");
        total_B += B.size();
    }

    ensuref(total_A <= 3000000, "Sum of lengths of all A exceeds 3_000_000: %lld", total_A);
    ensuref(total_B <= 3000000, "Sum of lengths of all B exceeds 3_000_000: %lld", total_B);

    inf.readEof();
}
