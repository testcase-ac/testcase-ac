#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        string input = inf.readToken("[01]{1,119}", "input");
        inf.readSpace();
        string output = inf.readToken("[01]{1,119}", "output");
        inf.readEoln();

        ensuref(input.size() == output.size(),
                "input and output lengths differ: %d vs %d",
                (int)input.size(), (int)output.size());
    }

    inf.readEof();
}
