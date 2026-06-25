#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string n = inf.readToken("[1-9][0-9]{0,25}", "n");
    ensuref(n.size() < 26 || n <= "10000000000000000000000000",
            "n exceeds 10^25: %s", n.c_str());
    inf.readEoln();
    inf.readEof();
}
