#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the length n: must be between 1 and 100 inclusive.
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    // Read the name: a single token of uppercase letters without spaces.
    // We allow any positive length here, but will check it equals n.
    string name = inf.readToken("[A-Z]+", "name");
    ensuref((int)name.size() == n,
            "The length of the name (%d) does not match n (%d)", 
            (int)name.size(), n);
    inf.readEoln();

    inf.readEof();
    return 0;
}
