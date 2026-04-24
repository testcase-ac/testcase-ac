#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 200, "N");
    inf.readEoln();

    // Read the string
    string s = inf.readToken("[^]+", "s");
    // Check length matches N
    ensuref((int)s.size() == N,
            "Length of string s (%d) does not match N (%d)", (int)s.size(), N);
    // Check all characters are one of ()[]{}?
    for (int i = 0; i < N; i++) {
        char c = s[i];
        bool ok = (c == '(' || c == ')' ||
                   c == '[' || c == ']' ||
                   c == '{' || c == '}' ||
                   c == '?');
        ensuref(ok, "Invalid character '%c' at position %d in s", c, i+1);
    }
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
