#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 5000000, "n");
    inf.readEoln();

    // Read the word of length exactly n, consisting only of letters and digits
    string s = inf.readLine("[A-Za-z0-9]{1,5000000}", "s");
    // Check exact length match
    ensuref((int)s.size() == n, "Length of string s is %d but expected %d", (int)s.size(), n);

    // Ensure no hidden number (i.e., run of consecutive digits) exceeds 6 digits
    int run = 0;
    for (int i = 0; i < n; i++) {
        if (isdigit(s[i])) {
            run++;
            ensuref(run <= 6,
                    "Hidden number too long: run of digits length %d at position ending %d",
                    run, i);
        } else {
            run = 0;
        }
    }

    // After the single test case, we must be at EOF
    inf.readEof();
    return 0;
}
