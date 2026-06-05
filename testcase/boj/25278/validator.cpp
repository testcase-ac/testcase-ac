#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 315, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string parameter = inf.readToken("oxygen|ocean|temperature", "parameter");
        inf.readSpace();

        string delta = inf.readToken("[^ ]{2,2}", "delta");
        ensuref(delta[0] == '+', "delta must start with '+': %s", delta.c_str());
        ensuref('1' <= delta[1] && delta[1] <= '5', "delta must be from +1 to +5: %s", delta.c_str());
        inf.readEoln();
    }

    inf.readEof();
}
