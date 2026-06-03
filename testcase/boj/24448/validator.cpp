#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(2, 200000, "Q");
    inf.readEoln();

    vector<string> stack;
    int readCount = 0;

    for (int i = 1; i <= q; ++i) {
        string s = inf.readToken("READ|[a-z]{1,10}", "S_i");
        inf.readEoln();

        if (s == "READ") {
            ++readCount;
            ensuref(!stack.empty(), "READ at action %d with no book on stack", i);
            stack.pop_back();
        } else {
            stack.push_back(s);
        }
    }

    ensuref(readCount >= 1, "there must be at least one READ action");
    inf.readEof();
}
