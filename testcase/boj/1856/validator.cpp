#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(1, 600, "w");
    inf.readSpace();
    int l = inf.readInt(2, 300, "l");
    inf.readEoln();

    string s = inf.readToken("[a-z]{2,300}", "S");
    ensuref((int)s.size() == l, "S length is %d, expected l=%d", (int)s.size(), l);
    inf.readEoln();

    for (int i = 0; i < w; ++i) {
        string word = inf.readToken("[a-z]{1,25}", "word");
        inf.readEoln();
    }

    inf.readEof();
}
