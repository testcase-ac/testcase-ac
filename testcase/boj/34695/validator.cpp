#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K and N
    int K = inf.readInt(1, 676, "K");
    inf.readSpace();
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    set<string> allowed;
    for (int i = 0; i < K; ++i) {
        string s = inf.readToken("[a-z]{2}", "allowed_pair");
        inf.readEoln();

        ensuref(allowed.count(s) == 0, "Duplicate allowed pair at line %d: %s", i + 2, s.c_str());
        allowed.insert(s);
    }

    inf.readEof();
}
