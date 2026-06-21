#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    for (int tc = 1; tc <= n; ++tc) {
        setTestCase(tc);

        int s = inf.readInt(1, 1000, "S");
        inf.readEoln();

        for (int i = 0; i < s; ++i) {
            if (i > 0) {
                inf.readSpace();
            }

            string rope = inf.readToken("[0-9]{1,3}[BR]", "rope");
            char color = rope.back();
            rope.pop_back();

            ensuref(rope == "0" || rope[0] != '0',
                    "rope length has leading zero in testcase %d, index %d", tc, i + 1);

            int length = stoi(rope);
            ensuref(1 <= length && length <= 100,
                    "rope length out of range in testcase %d, index %d: %d", tc, i + 1, length);
            ensuref(color == 'B' || color == 'R',
                    "rope color must be B or R in testcase %d, index %d", tc, i + 1);
        }
        inf.readEoln();
    }

    inf.readEof();
}
