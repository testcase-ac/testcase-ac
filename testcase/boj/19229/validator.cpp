#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int l = inf.readInt(1, 1000, "l");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    string letters = inf.readToken("[a-z]+", "letters");
    ensuref(static_cast<int>(letters.size()) == n * l,
            "letters length must be n*l: expected %d, found %d",
            n * l,
            static_cast<int>(letters.size()));
    inf.readEoln();
    inf.readEof();
}
