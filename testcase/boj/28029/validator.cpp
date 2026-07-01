#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[a-z]{1,200000}", "s");
    inf.readEoln();

    for (int i = 0; i < (int)s.size(); ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, 1000, "cost_i");
    }
    inf.readEoln();
    inf.readEof();
}
