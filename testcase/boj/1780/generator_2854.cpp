#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Possible values for each cell
    vector<int> vals = {-1, 0, 1};

    // Hyper-parameter: choose exponent k ∈ {0,1} so N = 3^k ∈ {1,3}
    int k = rnd.next(0, 1);
    int N = 1;
    for (int i = 0; i < k; ++i) N *= 3;

    // Hyper-parameter: probability to make the entire matrix uniform (only if N>1)
    double uniformProb = rnd.next(0.0, 1.0);
    bool fullUniform = (N > 1) && (rnd.next() < uniformProb);

    // Output N
    println(N);

    if (fullUniform) {
        // Choose one value and fill the whole matrix
        int v = rnd.any(vals);
        vector<int> row(N, v);
        for (int i = 0; i < N; ++i)
            println(row);
    } else {
        // Fill each cell randomly
        for (int i = 0; i < N; ++i) {
            vector<int> row;
            for (int j = 0; j < N; ++j)
                row.push_back(rnd.any(vals));
            println(row);
        }
    }

    return 0;
}
