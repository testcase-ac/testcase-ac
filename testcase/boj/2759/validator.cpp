#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The Korean statement and sample use a leading T. The embedded
    // English variant describes a sentinel N=0 format, which is not used here.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        // CHECK: The statement only gives N <= 30; N=0 would make the stack absent.
        int n = inf.readInt(1, 30, "N");

        vector<bool> seen(n + 1, false);
        for (int i = 1; i <= n; ++i) {
            inf.readSpace();
            int pancake = inf.readInt(1, n, "pancake");
            ensuref(!seen[pancake],
                    "duplicate pancake size %d at case %d position %d",
                    pancake,
                    tc,
                    i);
            seen[pancake] = true;
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
