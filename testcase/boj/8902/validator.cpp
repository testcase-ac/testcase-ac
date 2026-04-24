#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Read first lane string
        string s1 = inf.readToken("[A-Z]{1,5000}", "lane1");
        inf.readEoln();
        // Read second lane string
        string s2 = inf.readToken("[A-Z]{1,5000}", "lane2");
        inf.readEoln();
        // Additional sanity checks (redundant given regex, but clearer errors)
        ensuref(!s1.empty() && (int)s1.size() <= 5000,
                "Length of lane1 must be between 1 and 5000, got %d", (int)s1.size());
        ensuref(!s2.empty() && (int)s2.size() <= 5000,
                "Length of lane2 must be between 1 and 5000, got %d", (int)s2.size());
        for (int i = 0; i < (int)s1.size(); i++) {
            ensuref(s1[i] >= 'A' && s1[i] <= 'Z',
                    "lane1 contains invalid character '%c' at position %d", s1[i], i+1);
        }
        for (int i = 0; i < (int)s2.size(); i++) {
            ensuref(s2[i] >= 'A' && s2[i] <= 'Z',
                    "lane2 contains invalid character '%c' at position %d", s2[i], i+1);
        }
    }

    inf.readEof();
    return 0;
}
