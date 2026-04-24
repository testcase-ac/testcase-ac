#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of students in front of Seunghwan
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read the permutation of [1..N]
    vector<int> p = inf.readInts(N, 1, N, "p");
    inf.readEoln();

    // Check that it's indeed a permutation: no duplicates
    vector<char> seen(N+1, false);
    for (int i = 0; i < N; i++) {
        int x = p[i];
        ensuref(!seen[x],
                "Duplicate number %d at position %d", x, i+1);
        seen[x] = true;
    }

    inf.readEof();
    return 0;
}
