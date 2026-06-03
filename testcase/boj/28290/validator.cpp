#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[asdfjkl;]{8}", "S");
    inf.readEoln();

    set<char> seen(s.begin(), s.end());
    ensuref(seen.size() == 8, "S must contain each allowed character exactly once");
    for (char c : string("asdfjkl;")) {
        ensuref(seen.count(c) == 1, "S must contain character '%c' exactly once", c);
    }

    inf.readEof();
}
