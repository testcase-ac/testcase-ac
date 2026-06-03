#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string a = inf.readToken("[01]{1,100000}", "a");
    inf.readEoln();
    string b = inf.readToken("[01]{1,100000}", "b");
    inf.readEoln();

    ensuref(a.size() == b.size(), "a and b must have the same length: %d != %d",
            int(a.size()), int(b.size()));

    inf.readEof();
}
