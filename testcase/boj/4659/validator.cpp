#include "testlib.h"
#include <string>

using namespace std;

bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool isAcceptable(const string& s) {
    bool hasVowel = false;
    int n = (int)s.size();

    for (int i = 0; i < n; i++) {
        if (isVowel(s[i])) hasVowel = true;
    }

    if (!hasVowel) return false;

    // Rule 2: no 3 consecutive vowels or 3 consecutive consonants
    for (int i = 0; i + 2 < n; i++) {
        bool v1 = isVowel(s[i]);
        bool v2 = isVowel(s[i + 1]);
        bool v3 = isVowel(s[i + 2]);
        if (v1 == v2 && v2 == v3) return false;
    }

    // Rule 3: no same char twice in a row, except "ee" and "oo"
    for (int i = 0; i + 1 < n; i++) {
        if (s[i] == s[i + 1]) {
            if (!(s[i] == 'e' || s[i] == 'o')) return false;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        string pw = inf.readToken("[a-z]+", "password");
        caseCount++;

        // "end" is the terminating token and not a test case
        if (pw == "end") {
            // Do not count "end" as a test; ensure no extra data
            inf.readEoln();
            break;
        }

        // Length constraint: 1 to 20 characters
        ensuref(1 <= (int)pw.size() && (int)pw.size() <= 20,
                "password length must be between 1 and 20, got %d", (int)pw.size());

        // Validate that the password actually satisfies the problem's guarantees:
        // It must be either acceptable or not acceptable per problem rules; here
        // we just ensure our interpretation produces a consistent result (always true).
        // This is effectively always true, but left here as a placeholder for
        // potential additional global constraints.
        bool ok = isAcceptable(pw);
        (void)ok; // suppress unused warning

        inf.readEoln();
        ensuref(caseCount <= 100000, "too many test cases: %d", caseCount);
    }

    inf.readEof();
}
