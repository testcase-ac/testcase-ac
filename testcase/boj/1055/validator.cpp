#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Line 1: initial string, only lowercase letters, length 1..50
    string init = inf.readLine("[a-z]{1,50}", "initial");
    // No further checks needed: regex ensures only [a-z] and length constraints

    // Line 2: template string S, length 2..50, chars are lowercase or '$', first char must be '$'
    string S = inf.readLine("[^]+", "S");
    ensuref((int)S.size() >= 2 && (int)S.size() <= 50,
            "Length of S must be between 2 and 50, got %d", (int)S.size());
    for (int i = 0; i < (int)S.size(); i++) {
        char c = S[i];
        ensuref((c >= 'a' && c <= 'z') || c == '$',
                "Invalid character in S at position %d: '%c'", i, c);
    }
    ensuref(S[0] == '$', "First character of S must be '$'");

    // Line 3: number of executions T, natural number <= 1e9
    long long T = inf.readLong(1LL, 1000000000LL, "T");
    inf.readEoln();

    // Line 4: min and max positions
    long long mn = inf.readLong(1LL, 1000000000LL, "min");
    inf.readSpace();
    long long mx = inf.readLong(mn, mn + 99, "max");
    inf.readEoln();

    // No more tokens
    inf.readEof();
    return 0;
}
