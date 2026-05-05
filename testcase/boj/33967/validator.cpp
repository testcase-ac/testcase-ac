#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(2, 200000, "N");
    inf.readEoln();

    // 2. Read the design string (exactly N characters, only 2, 5, [, ])
    string s = inf.readToken("[^]+", "design");
    ensuref((int)s.size() == N, "Design string length does not match N: got %d, expected %d", (int)s.size(), N);

    // 3. Check that all characters are valid and first/last are [ and ]
    ensuref(s[0] == '[', "First character must be '['");
    ensuref(s[N-1] == ']', "Last character must be ']'");
    for (int i = 0; i < N; ++i) {
        char c = s[i];
        ensuref(c == '2' || c == '5' || c == '[' || c == ']', 
            "Invalid character at position %d: '%c'", i+1, c);
    }

    inf.readEoln();
    inf.readEof();
}
