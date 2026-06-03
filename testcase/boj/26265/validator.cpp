#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    set<pair<string, string>> pairs;
    for (int i = 0; i < n; ++i) {
        string mentor = inf.readToken("[a-z]{1,20}", "mentor");
        inf.readSpace();
        string mentee = inf.readToken("[a-z]{1,20}", "mentee");
        inf.readEoln();

        ensuref(pairs.insert({mentor, mentee}).second,
                "duplicate mentor-mentee pair at line %d: %s %s",
                i + 2, mentor.c_str(), mentee.c_str());
    }

    inf.readEof();
    return 0;
}
