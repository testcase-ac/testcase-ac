#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        int c = inf.readInt(1, 100, "c");
        inf.readSpace();
        int d = inf.readInt(1, 100, "d");
        inf.readSpace();
        int v = inf.readInt(0, 500, "v");
        inf.readEoln();

        for (int i = 0; i < v; i++) {
            string in_animal = inf.readToken("[CD]([1-9][0-9]?|100)", "vote_in");
            inf.readSpace();
            string out_animal = inf.readToken("[CD]([1-9][0-9]?|100)", "vote_out");
            inf.readEoln();

            char pc = in_animal[0];
            char qc = out_animal[0];
            ensuref((pc == 'C' && qc == 'D') || (pc == 'D' && qc == 'C'),
                    "Vote %d in test %d must contain one C and one D: got '%s' and '%s'",
                    i+1, tc, in_animal.c_str(), out_animal.c_str());

            auto parse_num = [&](const string &s) {
                int num = 0;
                for (size_t j = 1; j < s.size(); j++) {
                    num = num * 10 + (s[j] - '0');
                }
                return num;
            };

            int in_num = parse_num(in_animal);
            int out_num = parse_num(out_animal);

            if (pc == 'C') {
                ensuref(in_num >= 1 && in_num <= c,
                        "In-vote cat index out of range [1,%d]: %d in test %d vote %d",
                        c, in_num, tc, i+1);
            } else {
                ensuref(in_num >= 1 && in_num <= d,
                        "In-vote dog index out of range [1,%d]: %d in test %d vote %d",
                        d, in_num, tc, i+1);
            }
            if (qc == 'C') {
                ensuref(out_num >= 1 && out_num <= c,
                        "Out-vote cat index out of range [1,%d]: %d in test %d vote %d",
                        c, out_num, tc, i+1);
            } else {
                ensuref(out_num >= 1 && out_num <= d,
                        "Out-vote dog index out of range [1,%d]: %d in test %d vote %d",
                        d, out_num, tc, i+1);
            }
        }
    }

    inf.readEof();
    return 0;
}
