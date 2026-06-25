#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string a = inf.readToken("[1-9][0-9]{0,59}", "a");
    inf.readEoln();

    string b = inf.readToken("[1-9][0-9]{0,59}", "b");
    inf.readEoln();

    ensuref(a.size() == b.size(), "a and b must have the same length: %d vs %d",
            int(a.size()), int(b.size()));

    inf.readEof();
}
