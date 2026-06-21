#include "testlib.h"

#include <string>

using namespace std;

namespace {

string readStack(int length, int k, const char* name) {
    string stack = inf.readToken("[0-9]+", name);
    ensuref(static_cast<int>(stack.size()) == length,
            "%s length must be %d, found %d", name, length,
            static_cast<int>(stack.size()));

    for (int i = 0; i < length; ++i) {
        int digit = stack[i] - '0';
        ensuref(digit < k, "%s[%d] must be in [0, %d], found %d",
                name, i + 1, k - 1, digit);
    }

    return stack;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int g = inf.readInt(1, 3000, "G");
    inf.readEoln();

    int k = inf.readInt(1, 10, "K");
    inf.readSpace();
    int l = inf.readInt(1, 2000, "L");
    inf.readEoln();

    for (int game = 1; game <= g; ++game) {
        setTestCase(game);

        int n = inf.readInt(1, l, "N");
        inf.readEoln();
        readStack(n, k, "S");
        inf.readEoln();

        int m = inf.readInt(1, l, "M");
        inf.readEoln();
        readStack(m, k, "T");
        inf.readEoln();
    }

    inf.readEof();
}
