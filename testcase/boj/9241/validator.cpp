#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first DNA string (before infection)
    string s = inf.readLine("[AGCT]{1,100000}", "S");
    // Read second DNA string (after infection)
    string t = inf.readLine("[AGCT]{1,100000}", "T");

    // Ensure both lines are present and not empty (redundant due to regex, but for clarity)
    ensuref(!s.empty(), "First DNA string S is empty");
    ensuref(!t.empty(), "Second DNA string T is empty");

    // Ensure both lines are not longer than 1e5 (already checked by regex, but for clarity)
    ensuref(s.size() <= 100000, "First DNA string S is longer than 100000");
    ensuref(t.size() <= 100000, "Second DNA string T is longer than 100000");

    // No extra lines
    inf.readEof();
}
