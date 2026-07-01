#include "testlib.h"

#include <string>

using namespace std;

static bool isSpecial(const string& s) {
    for (int split = 1; split < static_cast<int>(s.size()); ++split) {
        string u = s.substr(0, split);
        string v = s.substr(split);
        if (!(u < v)) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[01]{1,50}", "S");
    inf.readEoln();
    ensuref(isSpecial(s), "S must be a special string");
    inf.readEof();
}
