#include "testlib.h"
#include <set>
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    set<string> seen_numbers;
    for (int i = 0; i < N; ++i) {
        string s = inf.readToken("[0-9A-Z]{1,50}", "number");
        inf.readEoln();

        // Check for duplicate numbers (not required by statement, but just in case)
        // Not needed, so commented out.
        // ensuref(seen_numbers.count(s) == 0, "Duplicate number at line %d: %s", i+2, s);
        // seen_numbers.insert(s);

        // Check for leading zeros (not allowed unless the number is "0")
        if (s.size() > 1) {
            ensuref(s[0] != '0', "Number at line %d has leading zeros: %s", i+2, s.c_str());
        }

        // Check all characters are valid 36-digit
        for (size_t j = 0; j < s.size(); ++j) {
            char c = s[j];
            ensuref((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z'),
                    "Invalid character '%c' in number at line %d, position %zu", c, i+2, j+1);
        }
    }

    // Read K
    int K = inf.readInt(0, 36, "K");
    inf.readEoln();

    inf.readEof();
}
