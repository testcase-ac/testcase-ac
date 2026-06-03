#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    int totalLength = 0;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
            ++totalLength;
        }
        string word = inf.readToken("[a-z]+", "word");
        totalLength += static_cast<int>(word.size());
    }
    inf.readEoln();
    inf.readEof();

    ensuref(totalLength <= 100, "message length including spaces is %d, expected at most 100", totalLength);
}
