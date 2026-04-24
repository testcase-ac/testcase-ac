#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of columns
    int N = inf.readInt(1, 300000, "N");
    inf.readEoln();

    // Counts of black cans in each column
    vector<int> b = inf.readInts(N, 0, 1000000, "black_i");
    inf.readEoln();

    // Counts of gray cans in each column
    vector<int> g = inf.readInts(N, 0, 1000000, "gray_i");
    inf.readEoln();

    // Counts of white cans in each column
    vector<int> w = inf.readInts(N, 0, 1000000, "white_i");
    inf.readEoln();

    // Number of shots
    int M = inf.readInt(1, 300000, "M");
    inf.readEoln();

    // Compute maximum stack height among all columns
    long long maxH = 0;
    for (int i = 0; i < N; i++) {
        long long sum = (long long)b[i] + g[i] + w[i];
        if (sum > maxH) maxH = sum;
    }
    // If all stacks are empty, there is no valid positive height to shoot
    ensuref(maxH > 0, "All columns are empty, so no valid shot height exists");

    // Heights at which shots are fired
    // Each height must be between 1 and maxH inclusive
    vector<int> h = inf.readInts(M, 1, (int)maxH, "h_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
