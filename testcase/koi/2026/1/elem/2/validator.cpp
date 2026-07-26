#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();
    string a = inf.readToken("[SRP]{1,200000}", "A");
    inf.readEoln();
    ensuref(static_cast<int>(a.size()) == n,
            "A must have length N: expected %d, found %d",
            n, static_cast<int>(a.size()));
    inf.readEof();
}
