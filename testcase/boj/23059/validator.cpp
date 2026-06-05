#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string a = inf.readToken("[a-z]{1,15}", "A");
        inf.readSpace();
        string b = inf.readToken("[a-z]{1,15}", "B");
        inf.readEoln();

        ensuref(a != b, "relation %d has equal item names: %s", i + 1, a.c_str());
    }

    inf.readEof();
}
