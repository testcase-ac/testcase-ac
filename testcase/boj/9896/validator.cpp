#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "n");
    inf.readEoln();

    string bits = inf.readToken("[01]{1,20}", "bits");
    ensuref((int)bits.size() == n, "bits length must be n: got %d, expected %d",
            (int)bits.size(), n);
    inf.readEoln();

    inf.readEof();
}
