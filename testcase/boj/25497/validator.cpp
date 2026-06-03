#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    string skills = inf.readToken("[1-9LRSK]{1,200000}", "skills");
    ensuref(static_cast<int>(skills.size()) == n,
            "skills length must equal N: length=%d, N=%d",
            static_cast<int>(skills.size()), n);
    inf.readEoln();

    inf.readEof();
}
