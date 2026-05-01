#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the remaining digits string S: 1 to 3000 digits, each 0-9.
    string s = inf.readLine("[0-9]{1,3000}", "s");

    // Ensure that this string can indeed come from deleting digits
    // in the sequence "1234567891011...". We try to match it as a subsequence
    // up to some sufficiently large Nmax.
    int L = (int)s.size();
    int idx = 0;
    const int Nmax = 200000;
    for (int n = 1; n <= Nmax && idx < L; ++n) {
        string t = to_string(n);
        for (char c : t) {
            if (idx < L && c == s[idx]) {
                idx++;
                if (idx == L) break;
            }
        }
    }
    ensuref(idx == L,
            "The input string is not a subsequence of the concatenation "
            "of numbers from 1 to %d", Nmax);

    inf.readEof();
    return 0;
}
