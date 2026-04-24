#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Read c, d, v
        int c = inf.readInt(1, 100, "c");
        inf.readSpace();
        int d = inf.readInt(1, 100, "d");
        inf.readSpace();
        int v = inf.readInt(0, 500, "v");
        inf.readEoln();

        for (int i = 0; i < v; i++) {
            // Read the two votes: one cat and one dog
            string in_animal = inf.readToken("[CD][0-9]+", "vote_in");
            inf.readSpace();
            string out_animal = inf.readToken("[CD][0-9]+", "vote_out");
            inf.readEoln();

            // Parse and validate
            char pc = in_animal[0];
            char qc = out_animal[0];
            // They must be different types: one C and one D
            ensuref((pc == 'C' && qc == 'D') || (pc == 'D' && qc == 'C'),
                    "Vote %d in test %d must contain one C and one D: got '%s' and '%s'",
                    i+1, tc, in_animal.c_str(), out_animal.c_str());

            // Helper to parse numeric part
            auto parse_num = [&](const string &s) {
                long long num = 0;
                // at least one digit after letter
                ensuref(s.size() >= 2, "Invalid vote token '%s'", s.c_str());
                for (size_t j = 1; j < s.size(); j++) {
                    char ch = s[j];
                    ensuref(ch >= '0' && ch <= '9',
                            "Invalid character '%c' in token '%s'", ch, s.c_str());
                    num = num * 10 + (ch - '0');
                    ensuref(num <= 1000000000LL,
                            "Parsed number too large in token '%s'", s.c_str());
                }
                return num;
            };

            long long in_num = parse_num(in_animal);
            long long out_num = parse_num(out_animal);

            // Validate ranges
            if (pc == 'C') {
                ensuref(in_num >= 1 && in_num <= c,
                        "In-vote cat index out of range [1,%d]: %lld in test %d vote %d",
                        c, in_num, tc, i+1);
            } else {
                // pc == 'D'
                ensuref(in_num >= 1 && in_num <= d,
                        "In-vote dog index out of range [1,%d]: %lld in test %d vote %d",
                        d, in_num, tc, i+1);
            }
            if (qc == 'C') {
                ensuref(out_num >= 1 && out_num <= c,
                        "Out-vote cat index out of range [1,%d]: %lld in test %d vote %d",
                        c, out_num, tc, i+1);
            } else {
                // qc == 'D'
                ensuref(out_num >= 1 && out_num <= d,
                        "Out-vote dog index out of range [1,%d]: %lld in test %d vote %d",
                        d, out_num, tc, i+1);
            }
        }
    }

    inf.readEof();
    return 0;
}
