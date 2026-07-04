#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20000000, "n");
    inf.readEoln();

    string sequence = inf.readToken("[AGCT]+", "sequence");
    ensuref((int)sequence.size() == n,
            "sequence length must be n: expected %d, found %d",
            n,
            (int)sequence.size());
    inf.readEoln();
    inf.readEof();
}
