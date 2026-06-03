#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, n, "A_i");
    inf.readEoln();

    bool hasCandidateOne = false;
    for (int i = 0; i < n; ++i) {
        if (a[i] == 1) {
            hasCandidateOne = true;
        }
    }
    ensuref(hasCandidateOne, "at least one student must vote for candidate 1");

    inf.readEof();
}
