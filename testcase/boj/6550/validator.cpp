#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_LEN = 100000;
    int test_cases = 0;
    long long total_len = 0;

    while (!inf.seekEof()) {
        string s = inf.readToken("[^ ]{0,100000}", "s"); // s: no spaces, up to 1e5
        inf.readSpace();
        string t = inf.readToken("[^ ]{0,100000}", "t"); // t: no spaces, up to 1e5
        inf.readEoln();

        ensuref((int)s.size() <= MAX_LEN, "Length of s (%d) exceeds 100000", (int)s.size());
        ensuref((int)t.size() <= MAX_LEN, "Length of t (%d) exceeds 100000", (int)t.size());

        // Only count test cases if at least one string is non-empty
        test_cases++;
        ensuref(test_cases <= 100000, "Number of test cases exceeds 100000");

        total_len += s.size();
        total_len += t.size();
        // Optionally, you may want to limit total input size, but not required by statement
    }

    inf.readEof();
}
