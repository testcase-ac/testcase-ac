#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(3, 100, "N");
    inf.readSpace();
    int M = inf.readInt(10, 300000, "M");
    inf.readEoln();

    // Read the card values
    vector<int> cards = inf.readInts(N, 1, 100000, "card");
    inf.readEoln();

    // Global check: there must exist at least one triple whose sum <= M
    // The smallest possible sum is of the three smallest cards
    vector<int> sorted = cards;
    sort(sorted.begin(), sorted.end());
    long long minSum = (long long)sorted[0] + sorted[1] + sorted[2];
    ensuref(minSum <= M,
            "No valid triple sum <= M: smallest three cards sum = %lld > M = %d",
            minSum, M);

    inf.readEof();
    return 0;
}
