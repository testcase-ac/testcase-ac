#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<int> inputSeq = inf.readInts(n, 1, 250000, "inputSeq");
    inf.readEoln();

    inf.readEof();
}
