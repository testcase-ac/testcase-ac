#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of papers
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    // Read citation counts
    vector<int> citations = inf.readInts(n, 0, 10000, "citation_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
