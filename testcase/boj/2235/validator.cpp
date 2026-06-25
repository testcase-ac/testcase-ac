#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int problemCount = 0;
    int sequenceCount = 0;

    while (true) {
        string permutation = inf.readLine("[A-Z#]{1,26}", "permutation_or_end");
        if (permutation == "#") {
            break;
        }

        ++problemCount;
        // CHECK: The statement gives no upper bound for the number of problems.
        ensuref(problemCount <= 100000, "too many problems: %d", problemCount);
        ensuref(permutation.size() == 26,
                "permutation must contain 26 uppercase letters, found %d",
                static_cast<int>(permutation.size()));

        set<char> letters(permutation.begin(), permutation.end());
        ensuref(letters.size() == 26, "permutation contains duplicate letters");

        int currentProblemSequences = 0;
        while (true) {
            string digits = inf.readLine("[0-9]{1,20}", "digits_or_zero");
            if (digits == "0") {
                break;
            }

            ++currentProblemSequences;
            ++sequenceCount;
            // CHECK: The statement gives no upper bound for the total number of digit strings.
            ensuref(sequenceCount <= 100000, "too many digit strings: %d", sequenceCount);
            ensuref(digits.size() >= 3,
                    "digit string must have length at least 3, found %d",
                    static_cast<int>(digits.size()));
        }

        ensuref(currentProblemSequences > 0, "problem %d has no digit strings", problemCount);
    }

    // CHECK: Reject vacuous input because the statement defines a series of encryption problems.
    ensuref(problemCount > 0, "input must contain at least one problem");
    inf.readEof();
}
