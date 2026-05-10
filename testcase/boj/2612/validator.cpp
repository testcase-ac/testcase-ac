#include "testlib.h"
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first DNA length
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();
    // Read first DNA sequence
    string s = inf.readLine("[ACGT]+", "first_dna");
    ensuref((int)s.size() == n,
            "Length of first DNA sequence does not match n: expected %d, got %d",
            n, (int)s.size());

    // Read second DNA length
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();
    // Read second DNA sequence
    string t = inf.readLine("[ACGT]+", "second_dna");
    ensuref((int)t.size() == m,
            "Length of second DNA sequence does not match m: expected %d, got %d",
            m, (int)t.size());

    // Check that there's at least one common character
    set<char> chars_in_s(s.begin(), s.end());
    bool has_common = false;
    for (char c : t) {
        if (chars_in_s.count(c)) {
            has_common = true;
            break;
        }
    }
    ensuref(has_common,
            "The two DNA sequences have no common character");

    inf.readEof();
    return 0;
}
