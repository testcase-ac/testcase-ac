#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 200, "N");
    inf.readSpace();
    int k = inf.readInt(1, 20, "K");
    (void)k;
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string word = inf.readToken("[a-z]{1,20}", format("word[%d]", i));
        (void)word;
        inf.readEoln();
    }

    inf.readEof();
}
