#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    string song = inf.readToken("[A-Z]{1,100}", "song");
    ensuref(static_cast<int>(song.size()) == n,
            "song length must be N: expected %d, found %d",
            n,
            static_cast<int>(song.size()));
    inf.readEoln();
    inf.readEof();
}
