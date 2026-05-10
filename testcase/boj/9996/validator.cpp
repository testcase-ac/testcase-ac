#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of files N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read the pattern: lowercase letters and exactly one '*', length ≤ 100
    string pattern = inf.readToken("[a-z*]{1,100}", "pattern");
    inf.readEoln();
    int cnt_star = count(pattern.begin(), pattern.end(), '*');
    ensuref(cnt_star == 1,
            "pattern must contain exactly one '*', but found %d", cnt_star);
    ensuref(pattern.front() != '*',
            "pattern must not start with '*'");
    ensuref(pattern.back() != '*',
            "pattern must not end with '*'");

    // Read N file names
    for (int i = 0; i < N; i++) {
        string fname = inf.readToken("[a-z]{1,100}", "filename");
        inf.readEoln();
        // Regex already ensures length ∈ [1,100] and only lowercase letters
        // No additional checks needed here
    }

    inf.readEof();
    return 0;
}
