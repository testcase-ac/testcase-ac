#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read sizes of A and B
    int nA = inf.readInt(1, 500000, "nA");
    inf.readSpace();
    int nB = inf.readInt(1, 500000, "nB");
    inf.readEoln();

    // Read elements of A
    vector<int> A = inf.readInts(nA, 1, 2147483647, "A_i");
    inf.readEoln();

    // Read elements of B
    vector<int> B = inf.readInts(nB, 1, 2147483647, "B_i");
    inf.readEoln();

    // Check uniqueness in A
    {
        vector<int> tmp = A;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < (int)tmp.size(); i++) {
            ensuref(tmp[i] != tmp[i-1],
                    "Duplicate element in A at value %d", tmp[i]);
        }
    }

    // Check uniqueness in B
    {
        vector<int> tmp = B;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < (int)tmp.size(); i++) {
            ensuref(tmp[i] != tmp[i-1],
                    "Duplicate element in B at value %d", tmp[i]);
        }
    }

    inf.readEof();
    return 0;
}
