#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 7, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M");
    inf.readEoln();

    // Read the N distinct natural numbers
    vector<int> a = inf.readInts(N, 1, 10000, "a_i");
    inf.readEoln();

    // Check for duplicates
    {
        set<int> s(a.begin(), a.end());
        ensuref((int)s.size() == N,
                "Input numbers must be distinct, but found %d unique out of %d",
                (int)s.size(), N);
    }

    // No more input
    inf.readEof();
    return 0;
}
