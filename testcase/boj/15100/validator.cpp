#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string a = inf.readToken("[a-z]{1,100000}", "A");
    inf.readEoln();
    string b = inf.readToken("[a-z]{1,100000}", "B");
    inf.readEoln();

    ensuref(a.size() == b.size(),
            "A and B must have the same length: %d vs %d",
            int(a.size()), int(b.size()));
    ensuref(a != b, "A and B must not be identical");

    inf.readEof();
}
