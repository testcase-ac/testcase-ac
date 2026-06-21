#include "testlib.h"

#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCases = inf.readInt(1, 5, "N");
    inf.readEoln();

    for (int t = 1; t <= testCases; ++t) {
        setTestCase(t);

        int segments = inf.readInt(1, 1000, "S");
        inf.readEoln();

        for (int i = 1; i <= segments; ++i) {
            string token = inf.readToken("[1-9][0-9]{0,2}[BR]", "segment");
            int length = atoi(token.substr(0, token.size() - 1).c_str());
            ensuref(length <= 100, "segment %d has length %d, expected at most 100", i, length);

            if (i < segments) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
