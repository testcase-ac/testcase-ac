#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the number of students N
    int N = inf.readInt(1, 20000, "N");
    inf.readEoln();

    // Read the permutation of size N
    vector<bool> seen(N+1, false);
    vector<int> a = inf.readInts(N, 1, N, "a_i");
    inf.readEoln();

    // Check for duplicates
    for (int i = 0; i < N; ++i) {
        int x = a[i];
        ensuref(!seen[x],
                "Duplicate number %d found at position %d", 
                x, i+1);
        seen[x] = true;
    }

    inf.readEof();
    return 0;
}
