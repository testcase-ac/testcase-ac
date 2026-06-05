#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000001, "n");
    inf.readEoln();

    string u = inf.readToken("[A-Z]+", "u");
    ensuref(static_cast<int>(u.size()) == n,
            "u length must equal n: expected %d, found %d",
            n,
            static_cast<int>(u.size()));
    inf.readEoln();

    inf.readEof();
}
