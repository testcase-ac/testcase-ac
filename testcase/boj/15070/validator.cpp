#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 10, "n");
    inf.readEoln();

    set<string> names;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        // CHECK: The statement does not specify name length or alphabet; accept
        // any visible non-whitespace token up to a practical contest-name cap.
        string name = inf.readToken("[!-~]{1,100}", "name");
        // CHECK: "n names of all participating players" is interpreted as
        // distinct player identifiers.
        ensuref(names.insert(name).second, "duplicate player name: %s", name.c_str());
    }
    inf.readEoln();

    inf.readToken("[WB]{1,1000}", "scores");
    inf.readEoln();
    inf.readEof();
}
