#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    string dna = inf.readToken("[ACGT]{1,10000}", "dna");
    ensuref((int)dna.size() == n, "dna length is %d, expected %d", (int)dna.size(), n);
    inf.readEoln();

    inf.readEof();
}
