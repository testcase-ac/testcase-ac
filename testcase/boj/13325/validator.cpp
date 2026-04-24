#include "testlib.h"
#include <vector>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read tree height k
    int k = inf.readInt(1, 20, "k");
    inf.readEoln();

    // The number of edges in a full binary tree of height k is sum_{i=1..k} 2^i = 2^{k+1} - 2
    long long totalEdgesLL = (1LL << (k + 1)) - 2;
    // totalEdgesLL <= 2^21 - 2 = 2097150, fits in int
    int totalEdges = int(totalEdgesLL);

    // Read all edge weights
    vector<int> w = inf.readInts(totalEdges, 1, 1000, "weight");
    inf.readEoln();

    inf.readEof();
    return 0;
}
