#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for T; keep the repo-standard
    // practical cap for an unspecified number of test cases.
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    const set<string> allowedGrades = {
        "0", "0.0", "0.7",
        "1", "1.0", "1.3", "1.7",
        "2", "2.0", "2.3", "2.7",
        "3", "3.0", "3.3", "3.7",
        "4", "4.0", "4.3",
    };

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 10, "N");
        inf.readEoln();

        for (int i = 1; i <= N; ++i) {
            inf.readInt(1, 6, "C");
            inf.readSpace();
            string G = inf.readToken("[0-9.]+", "G");
            int dotCount = 0;
            for (char ch : G) {
                if (ch == '.') {
                    ++dotCount;
                }
            }
            ensuref(dotCount <= 1,
                    "invalid grade format '%s' at semester %d course %d",
                    G.c_str(), tc, i);
            if (dotCount == 1) {
                size_t dot = G.find('.');
                ensuref(dot == 1 && dot + 2 == G.size(),
                        "invalid grade format '%s' at semester %d course %d",
                        G.c_str(), tc, i);
            } else {
                ensuref(G.size() == 1,
                        "invalid grade format '%s' at semester %d course %d",
                        G.c_str(), tc, i);
            }
            ensuref(allowedGrades.count(G) != 0,
                    "invalid grade '%s' at semester %d course %d",
                    G.c_str(), tc, i);
            inf.readEoln();
        }
    }

    inf.readEof();
}
