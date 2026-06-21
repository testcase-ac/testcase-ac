#include "testlib.h"

#include <string>

using namespace std;

namespace {

const string kMaxN = "100000000000000000000";

void validateN(const string& n, int caseIndex) {
    ensuref(n.size() < kMaxN.size() || n <= kMaxN,
            "N at case %d exceeds 10^20: %s", caseIndex, n.c_str());
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 500, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);
        string n = inf.readToken("[1-9][0-9]{0,20}", "N");
        validateN(n, tc);
        inf.readEoln();
    }

    inf.readEof();
}
